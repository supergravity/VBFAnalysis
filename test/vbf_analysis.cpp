#include <iostream>
#include <vector>
#include <map>
#include <fstream>

#include <TFile.h>
#include <TTree.h>

#include <boost/program_options.hpp>
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/classification.hpp"
#include "boost/algorithm/string/predicate.hpp"

#include "../interface/EventAnalysis.h"
#include "../interface/makePlot.h"

using namespace std;
using namespace boost;
namespace po = boost::program_options;


string filename_;
string datfilename_;
string outdir_;
double lumi_;
bool doTree_;
bool makeHStack_;
bool sideband_ = false;
bool logscale_ = false;
bool addsignal_= false;
bool normtodata_ = false;

map<string,double> Weight;
map<string,string> datatype;

vector<string> filename;
map<string,string> histo1DInfo;
map<string,string> outfile;

void OptionParser(int argc, char* argv[]){

	po::options_description desc("Allowed options");
	desc.add_options()
		("help"                                                                                ,"Help"                        )
		("infilename,i" , po::value<string>(&filename_)    ->default_value("")                 ,"input file name"             )
		("datfilename,d", po::value<string>(&datfilename_) ->default_value("vbfinfo.dat")      ,"input dat file name"         )
		("outdir,o"     , po::value<string>(&outdir_)      ->default_value("result/output")    ,"output directory"            )
		("LUMI"         , po::value<double>(&lumi_)        ->default_value(1.00)               ,"current luminosity"          )
		("doTree"       , po::value<bool>(&doTree_)        ->default_value(true)               ,"produce Tree"                )
		("makeHStack"   , po::value<bool>(&makeHStack_)    ->default_value(true)               ,"make 1DHisto stack plots"    )
		("SideBand"                                                                            ,"keep ONLY sideband region"   )
		("LogScale"                                                                            ,"Make plots with Y log scale" )
		("AddSignal"                                                                           ,"Add Signal MC into plots"    )
		("NormToData"                                                                          ,"Normalize to data"           )
		;
	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);
	if(vm.count("help")){cout << desc <<endl; exit(1);}
	if(vm.count("SideBand"))   sideband_    = true;
	if(vm.count("LogScale"))   logscale_    = true;
	if(vm.count("AddSignal"))  addsignal_   = true;
	if(vm.count("NormToData")) normtodata_  = true;

}

int main(int argc, char* argv[]){

	OptionParser(argc,argv);

	system(Form("mkdir -p %s",outdir_.c_str()));

	ifstream datfile;
	datfile.open(datfilename_.c_str());

	while(datfile.good()){
              
              string line;
	      getline(datfile,line);
	      if(line.substr(0,1) == "#" || line.substr(0,1) == " " || line == "\n" || line.empty()) continue;
              vector<string> els;
	      split(els,line,boost::is_any_of(" "));
            
	      string sampletype = els[0];
              string filetype   = els[1];
	      double Xsec       = boost::lexical_cast<double>(els[2]);
              double br         = boost::lexical_cast<double>(els[3]); 
              double GenNum     = boost::lexical_cast<double>(els[4]);
	      double generic    = 1.;
	      if(sampletype!="data") generic = Xsec*1000.*br*lumi_/GenNum;

	      Weight.insert(std::pair<string,double>(filetype,generic));
	      datatype.insert(std::pair<string,string>(filetype,sampletype));

	}
	split(filename,filename_,boost::is_any_of(","));

	for(vector<string>::iterator it = filename.begin();it != filename.end(); ++it){

	    TFile* myfile = new TFile((*it).c_str());
	    TTree* mytree = (TTree*)myfile -> Get("vbfTagDumper/trees/vbftag_80X_ichep_all");

            string tmpfilename = *it;
	    std::size_t find_slash = tmpfilename.find_last_of("/");
	    std::size_t find_dot   = tmpfilename.find_last_of(".");
	    string finalfilename = tmpfilename.substr(find_slash+1,find_dot-find_slash-1);

	    EventAnalysis DumperCore(mytree, finalfilename ,datatype[finalfilename] , Weight[finalfilename],outdir_ );
            DumperCore.EventDumperLoop(doTree_,sideband_);
	    if(it == filename.begin()) histo1DInfo = DumperCore.gethisto1Info();
            outfile.insert(std::pair<string,string>(DumperCore.getoutfile(),datatype[finalfilename]));
            delete myfile;

	}
      
	if(makeHStack_){

	   makePlot myfinalPlot(outfile,outdir_);
           for(map<string,string>::iterator it = histo1DInfo.begin();it != histo1DInfo.end(); ++it){
               
	       myfinalPlot.makeStackPlot(it->first,(it->second).c_str(),logscale_,addsignal_,normtodata_);
	   }
	}
	return 0;
}
