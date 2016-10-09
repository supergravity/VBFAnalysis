#ifndef __EVENTANALYSIS__
#define __EVENTANALYSIS__

#include <iostream>
#include <string>
#include <map>

#include "TTree.h"

class EventAnalysis{

	public:
		EventAnalysis(TTree* inputTree, std::string infilename, std::string samepletype, double eventWeight, std::string outdir);
		~EventAnalysis();
		void EventDumperLoop(bool doTree, bool doSideBand);
		std::map<std::string,std::string> gethisto1Info();
		std::string getoutfile();


	private:

		TTree* _inputTree;
		std::string _infilename;
		std::string _sampletype;
		std::string _outfilename;
		double _eventWeight;
		std::string _outdir;
                std::map<std::string,std::string> _1DHistoInfo;

		void Initialization();
		//Variables
		Float_t dipho_mass         ; 
	        Float_t dipho_leadPt       ;
	        Float_t dipho_leadEta      ;
	        Float_t dipho_leadPhi      ;
	        Float_t dipho_subleadPt    ;
	        Float_t dipho_subleadEta   ;
	        Float_t dipho_subleadPhi   ;
	        Float_t dipho_sublead_ptoM ;
	        Float_t dipho_leadIDMVA    ;
	        Float_t dipho_subleadIDMVA ;
                //VBFMVA(dijet BDT)	
	        Float_t dijet_abs_dEta     ;
	        Float_t dijet_LeadJPt      ;
	        Float_t dijet_SubJPt       ;
	        Float_t dijet_leadEta      ;
	        Float_t dijet_subleadEta   ;
                Float_t dijet_Mjj          ;
		Float_t dijet_Zep          ;
		Float_t dijet_dPhi_trunc   ;
	        Float_t dipho_lead_ptoM    ;
		Float_t leadPho_PToM       ;
		Float_t sublPho_PToM       ;

	        Float_t dijet_mva          ;
	        Float_t dipho_mva          ;
	        Float_t dipho_dijet_MVA    ;

		Int_t nvtx                 ;
		Float_t puweight           ;
		Float_t weight             ;
		 

		//OutoutTree
		Float_t Mgg                ;
		Float_t dijet_BDT          ;
		Float_t puWgt              ;
		Float_t allWgt             ;


};

#endif
