#ifndef __MAKEPLOT__
#define __MAKEPLOT__

#include <iostream>
#include <string>
#include <map>



class makePlot{

	public:
	
	makePlot( std::map<std::string,std::string> infile, std::string outdir );
	~makePlot();
        void makeStackPlot( std::string plotname, std::string Xaxisname, bool SetLogScale, bool AddSignalMC, bool NormToData );


	private:

	std::map<std::string,std::string> _infile;
	std::string _outdir;

};

#endif
