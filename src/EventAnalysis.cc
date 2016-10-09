#include <iostream>
#include <string>

#include "TFile.h"
#include "TH1D.h"

#include "../interface/EventAnalysis.h"


using namespace std;

EventAnalysis::EventAnalysis(TTree* inputTree, string infilename, string sampletype, double eventWeight, string outdir):
	_inputTree(inputTree),
	_infilename(infilename),
	_sampletype(sampletype),
	_eventWeight(eventWeight),
	_outdir(outdir)
{
	cout<<"[INFO]: Build the Constructor" << endl;
}

EventAnalysis::~EventAnalysis()
{
	cout<<"[INFO]: Call the destructor" << endl;
}

void EventAnalysis::Initialization(){

	cout << "[INFO]: Initializing  "<<_infilename<<"  ..." << endl;

	_inputTree -> SetBranchAddress("dipho_mass"           ,&dipho_mass            );
	_inputTree -> SetBranchAddress("dipho_leadPt"         ,&dipho_leadPt          );
	_inputTree -> SetBranchAddress("dipho_leadEta"        ,&dipho_leadEta         );
	_inputTree -> SetBranchAddress("dipho_leadPhi"        ,&dipho_leadPhi         );
	_inputTree -> SetBranchAddress("dipho_subleadPt"      ,&dipho_subleadPt       );
	_inputTree -> SetBranchAddress("dipho_subleadEta"     ,&dipho_subleadEta      );
	_inputTree -> SetBranchAddress("dipho_subleadPhi"     ,&dipho_subleadPhi      );
	_inputTree -> SetBranchAddress("dipho_sublead_ptoM"   ,&dipho_sublead_ptoM    );
	_inputTree -> SetBranchAddress("dipho_leadIDMVA"      ,&dipho_leadIDMVA       );
	_inputTree -> SetBranchAddress("dipho_subleadIDMVA"   ,&dipho_subleadIDMVA    );
	_inputTree -> SetBranchAddress("dijet_abs_dEta"       ,&dijet_abs_dEta        );
	_inputTree -> SetBranchAddress("dijet_LeadJPt"        ,&dijet_LeadJPt         );
	_inputTree -> SetBranchAddress("dijet_SubJPt"         ,&dijet_SubJPt          );
	_inputTree -> SetBranchAddress("dijet_leadEta"        ,&dijet_leadEta         );
	_inputTree -> SetBranchAddress("dijet_subleadEta"     ,&dijet_subleadEta      );
	_inputTree -> SetBranchAddress("dijet_Mjj"            ,&dijet_Mjj             );
	_inputTree -> SetBranchAddress("dijet_Zep"            ,&dijet_Zep             );
	_inputTree -> SetBranchAddress("dijet_dPhi_trunc"     ,&dijet_dPhi_trunc      );
	_inputTree -> SetBranchAddress("dipho_lead_ptoM"      ,&dipho_lead_ptoM       );
	_inputTree -> SetBranchAddress("leadPho_PToM"         ,&leadPho_PToM          );
	_inputTree -> SetBranchAddress("sublPho_PToM"         ,&sublPho_PToM          );
	_inputTree -> SetBranchAddress("dijet_mva"            ,&dijet_mva             );
	_inputTree -> SetBranchAddress("dipho_mva"            ,&dipho_mva             );
	_inputTree -> SetBranchAddress("dipho_dijet_MVA"      ,&dipho_dijet_MVA       );
	_inputTree -> SetBranchAddress("nvtx"                 ,&nvtx                  );
	_inputTree -> SetBranchAddress("puweight"             ,&puweight              );
	_inputTree -> SetBranchAddress("weight"               ,&weight                );
	//...

	cout << "[INFO]: Initialization is finished." << endl;

}


void EventAnalysis::EventDumperLoop(bool doTree, bool doSideBand){

	Initialization();

	TFile* outfile = new TFile(Form("%s/output_%s.root",_outdir.c_str(),_infilename.c_str()),"recreate");
	TTree* outTree = NULL;
	if(doTree){
	   outTree = new TTree(Form("output_%s",_inputTree->GetName()),"");	

	   outTree -> Branch("Mgg"       ,&Mgg            ,"Mgg/F"         );
	   outTree -> Branch("BDT"       ,&dijet_BDT      ,"dijet_BDT/F"   );
	   outTree -> Branch("puWgt"     ,&puWgt          ,"puWgt/F"       );
	   outTree -> Branch("allWgt"    ,&allWgt         ,"allWgt/F"      );
	}

	TH1D* h1_Mgg               = new TH1D("h1_Mgg"              ,""   ,40  ,100. ,180.   );    h1_Mgg               -> Sumw2();      
	TH1D* h1_Mjj               = new TH1D("h1_Mjj"              ,""   ,30  ,150. ,3500.  );    h1_Mjj               -> Sumw2(); 
	TH1D* h1_lead_phoPt        = new TH1D("h1_lead_phoPt"       ,""   ,30  ,20.  ,260.   );    h1_lead_phoPt        -> Sumw2(); 
	TH1D* h1_subl_phoPt        = new TH1D("h1_subl_phoPt"       ,""   ,30  ,20.  ,140.   );    h1_subl_phoPt        -> Sumw2(); 
	TH1D* h1_lead_phoEta       = new TH1D("h1_lead_phoEta"      ,""   ,30  ,-3.  ,3.     );    h1_lead_phoEta       -> Sumw2(); 
	TH1D* h1_subl_phoEta       = new TH1D("h1_subl_phoEta"      ,""   ,30  ,-3.  ,3.     );    h1_subl_phoEta       -> Sumw2(); 
	TH1D* h1_lead_jetPt        = new TH1D("h1_lead_jetPt"       ,""   ,30  ,20.  ,290.   );    h1_lead_jetPt        -> Sumw2(); 
	TH1D* h1_subl_jetPt        = new TH1D("h1_subl_jetPt"       ,""   ,30  ,10.  ,160.   );    h1_subl_jetPt        -> Sumw2(); 
	TH1D* h1_lead_jetEta       = new TH1D("h1_lead_jetEta"      ,""   ,40  ,-5.  ,5.     );    h1_lead_jetEta       -> Sumw2(); 
	TH1D* h1_subl_jetEta       = new TH1D("h1_subl_jetEta"      ,""   ,40  ,-5.  ,5.     );    h1_subl_jetEta       -> Sumw2(); 
	TH1D* h1_dijetDelEta       = new TH1D("h1_dijetDelEta"      ,""   ,30  ,2.   ,8.     );    h1_dijetDelEta       -> Sumw2(); 
	TH1D* h1_dijet_Zep         = new TH1D("h1_dijet_Zep"        ,""   ,30  ,-2.  ,8.     );    h1_dijet_Zep         -> Sumw2(); 
	TH1D* h1_dijet_dPhi_trunc  = new TH1D("h1_dijet_dPhi_trunc" ,""   ,30  ,-2.  ,8.     );    h1_dijet_dPhi_trunc  -> Sumw2(); 
	TH1D* h1_leadPho_PToM      = new TH1D("h1_leadPho_PToM"     ,""   ,30  ,0.   ,300.   );    h1_leadPho_PToM      -> Sumw2(); 
	TH1D* h1_sublPho_PToM      = new TH1D("h1_sublPho_PToM"     ,""   ,30  ,0.   ,300.   );    h1_sublPho_PToM      -> Sumw2(); 
	TH1D* h1_dipho_mva         = new TH1D("h1_dipho_mva"        ,""   ,40  ,-1.  ,1.     );    h1_dipho_mva         -> Sumw2(); 
	TH1D* h1_dijet_mva         = new TH1D("h1_dijet_mva"        ,""   ,20  ,0.4  ,1.     );    h1_dijet_mva         -> Sumw2(); 
	TH1D* h1_dipho_dijet_mva   = new TH1D("h1_dipho_dijet_mva"  ,""   ,40  ,-0.2 ,1.     );    h1_dipho_dijet_mva   -> Sumw2(); 
	TH1D* h1_dipho_id1_mva     = new TH1D("h1_dipho_id1_mva"    ,""   ,40  ,-1.  ,1.     );    h1_dipho_id1_mva     -> Sumw2(); 
	TH1D* h1_dipho_id2_mva     = new TH1D("h1_dipho_id2_mva"    ,""   ,40  ,-1.  ,1.     );    h1_dipho_id2_mva     -> Sumw2(); 
	TH1D* h1_nvtx              = new TH1D("h1_nvtx"             ,""   ,40  ,0.   ,40.    );    h1_nvtx              -> Sumw2(); 

        _1DHistoInfo[h1_Mgg             ->GetName()] = "M_{#gamma#gamma} (GeV/c^{2})"; 
        _1DHistoInfo[h1_Mjj             ->GetName()] = "M_{jj} (GeV/c^{2}";            
        _1DHistoInfo[h1_lead_phoPt      ->GetName()] = "Pt_{#gamma 1}(GeV)";           
        _1DHistoInfo[h1_subl_phoPt      ->GetName()] = "Pt_{#gamma 2}(GeV)";           
        _1DHistoInfo[h1_lead_phoEta     ->GetName()] = "#eta_{#gamma 1}";              
        _1DHistoInfo[h1_subl_phoEta     ->GetName()] = "#eta_{#gamma 2}";              
        _1DHistoInfo[h1_lead_jetPt      ->GetName()] = "Pt_{jet 1}(GeV)";              
        _1DHistoInfo[h1_subl_jetPt      ->GetName()] = "Pt_{jet 2}(GeV)";              
        _1DHistoInfo[h1_lead_jetEta     ->GetName()] = "#eta_{jet 1}";                 
        _1DHistoInfo[h1_subl_jetEta     ->GetName()] = "#eta_{jet 2}";                 
        _1DHistoInfo[h1_dijetDelEta     ->GetName()] = "#Delta#eta_{jj}";              
        _1DHistoInfo[h1_dijet_Zep       ->GetName()] = "Zeppenfeld";                   
        _1DHistoInfo[h1_dijet_dPhi_trunc->GetName()] = "#Delta#phi(jj,#gamma#gamma)";  
        _1DHistoInfo[h1_leadPho_PToM    ->GetName()] = "Pt(#gamma 1)/M_{#gamma#gamma}";
        _1DHistoInfo[h1_sublPho_PToM    ->GetName()] = "Pt(#gamma 2)/M_{#gamma#gamma}";
        _1DHistoInfo[h1_dipho_mva       ->GetName()] = "diphoton MVA";                 
        _1DHistoInfo[h1_dijet_mva       ->GetName()] = "dijet BDT score";              
        _1DHistoInfo[h1_dipho_dijet_mva ->GetName()] = "combined MVA";                 
        _1DHistoInfo[h1_dipho_id1_mva   ->GetName()] = "Photon1 ID MVA";               
        _1DHistoInfo[h1_dipho_id2_mva   ->GetName()] = "Photon2 ID MVA";               
        _1DHistoInfo[h1_nvtx            ->GetName()] = "nvtx";                         

	cout << "[INFO]: Start dumping "<< _infilename << endl;
	for(int entry=0;entry<_inputTree->GetEntries();entry++){
            _inputTree->GetEntry(entry);
            //You can add your own cuts here

	    if(doSideBand){
	       if(!( _sampletype == "vbf" || _sampletype == "ggf" )) 
		  if(dipho_mass>120. && dipho_mass<130.) continue;
	    }

	    double AllWgt = _eventWeight * puweight;


	    h1_Mgg                 -> Fill(dipho_mass         ,AllWgt);   
	    h1_Mjj                 -> Fill(dijet_Mjj          ,AllWgt); 
            h1_lead_phoPt          -> Fill(dipho_leadPt       ,AllWgt); 
	    h1_subl_phoPt          -> Fill(dipho_subleadPt    ,AllWgt); 
	    h1_lead_phoEta         -> Fill(dipho_leadEta      ,AllWgt); 
	    h1_subl_phoEta         -> Fill(dipho_subleadEta   ,AllWgt); 
            h1_lead_jetPt          -> Fill(dijet_LeadJPt      ,AllWgt);   
	    h1_subl_jetPt          -> Fill(dijet_SubJPt       ,AllWgt);  
	    h1_lead_jetEta         -> Fill(dijet_leadEta      ,AllWgt);     
	    h1_subl_jetEta         -> Fill(dijet_subleadEta   ,AllWgt);      
	    h1_dijetDelEta         -> Fill(dijet_abs_dEta     ,AllWgt);      
	    h1_dijet_Zep           -> Fill(dijet_Zep          ,AllWgt);        
	    h1_dijet_dPhi_trunc    -> Fill(dijet_dPhi_trunc   ,AllWgt);    
	    h1_leadPho_PToM        -> Fill(leadPho_PToM       ,AllWgt);  
	    h1_sublPho_PToM        -> Fill(sublPho_PToM       ,AllWgt);  
            h1_dipho_mva           -> Fill(dipho_mva          ,AllWgt);   
	    h1_dijet_mva           -> Fill(dijet_mva          ,AllWgt);       
	    h1_dipho_dijet_mva     -> Fill(dipho_dijet_MVA    ,AllWgt);       
	    h1_dipho_id1_mva       -> Fill(dipho_leadIDMVA    ,AllWgt);      
	    h1_dipho_id2_mva       -> Fill(dipho_subleadIDMVA ,AllWgt);      
	    h1_nvtx                -> Fill(nvtx               ,AllWgt);     

            if(doTree){

       	       Mgg          =   dipho_mass  ;
	       dijet_BDT    =   dijet_mva   ;
	       puWgt        =   puweight    ;
	       allWgt       =   AllWgt      ;

               outTree -> Fill();
	    }
	}//entry++

	cout << "[INFO]: Dumping of "<<_infilename<<" is finished !!!" << endl;

        outfile  ->  Write();
        outfile  ->  Close();

        delete outfile;

}

map<string,string> EventAnalysis::gethisto1Info(){

	return _1DHistoInfo;
}

string EventAnalysis::getoutfile(){

	_outfilename = _outdir + "/output_" + _infilename + ".root";
	return _outfilename;

}
