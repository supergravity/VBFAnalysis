#include <iostream>
#include <cmath>

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TH1D.h"
#include "TLorentzVector.h"

#define LUMI 12.889

using namespace std;

int main(){
     
	//Option
	//====================================================================================================
	  bool SideBand = true ;
          bool MCweight = false;

	//Input and Ouput Files Path
        //====================================================================================================
	  TString inpath  = "/wk_cms/youying/public/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2_v2/";
	  TString outpath = "output/";

	  system("mkdir -p " + outpath);

	//Input MC Samples( signals and backgrounds ) and real data
	//====================================================================================================
	  const int numberoffiles = 10;
	  TString filenames[numberoffiles];
	  filenames[0]  = "VBFHToGG_M125_13TeV_amcatnlo_pythia8.root"                                    ;
	  filenames[1]  = "GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root"                             ;
	  filenames[2]  = "GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8.root"  ;
	  filenames[3]  = "GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root"  ;
	  filenames[4]  = "GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root" ;
	  //filenames[5]  = "DiPhotonJets_MGG-80toInf_13TeV_amcatnloFXFX_pythia8.root";
	  filenames[5]  = "DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root"                                ;
	  filenames[6]  = "QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root"   ;
	  filenames[7]  = "QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root"  ;
	  filenames[8]  = "QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8.root"   ;
	  filenames[9]  = "Run2016BCD_ICHEP_PromptReco_v2.root"                                          ;

        //MC Information
	//====================================================================================================
	//Branching Ratio(Higgs -> gamma gamma)
          double BR = 2.27e-3;
        //Cross Section 
	  double VBF_Xsec  = 3.782  *1000 *BR;
	  double GGF_Xsec  = 48.58  *1000 *BR;
	  double GJ1_Xsec  = 3216.  *0.   ;//0.0 is just that I don't want to see this component.
	  double GJ2_Xsec  = 220.   *1000 ;
	  double GJ3_Xsec  = 850.8  *1000 ;
	  double GG_Xsec   = 84.4   *1000 ;
	  double QCD1_Xsec = 22110. *0.0  ;
	  double QCD2_Xsec = 113400.*0.0  ;
	  double QCD3_Xsec = 260500.*0.0  ;
        //Gen Number
	  double VBF_genN  = 1199200;
	  double GGF_genN  = 1022140;
	  double GJ1_genN  = 38336063;
	  double GJ2_genN  = 24616470;
	  double GJ3_genN  = 69679664;
	  double GG_genN   = 58432739;
	  double QCD1_genN = 17976699;
	  double QCD2_genN = 20219661;
	  double QCD3_genN = 35913224;
        //Normalization Factor
	  double norm[10];
	  norm[0] = VBF_Xsec  * LUMI / VBF_genN  ;
	  norm[1] = GGF_Xsec  * LUMI / GGF_genN  ;
	  norm[2] = GJ1_Xsec  * LUMI / GJ1_genN  ;
	  norm[3] = GJ2_Xsec  * LUMI / GJ2_genN  ;
	  norm[4] = GJ3_Xsec  * LUMI / GJ3_genN  ;
	  norm[5] = GG_Xsec   * LUMI / GG_genN   ;
	  norm[6] = QCD1_Xsec * LUMI / QCD1_genN ;
	  norm[7] = QCD2_Xsec * LUMI / QCD2_genN ;
	  norm[8] = QCD3_Xsec * LUMI / QCD3_genN ;
	  norm[9] = 1. ;

	  
	  TString treename = "vbfTagDumper/trees/vbftag_80X_ichep_all";	
	  TFile* myfiles[numberoffiles];
          TTree* mytrees[numberoffiles];	
	  for(int i=0;i<numberoffiles;i++){
              myfiles[i] = TFile::Open( inpath + filenames[i] );
              mytrees[i] = (TTree*)myfiles[i] ->Get( treename );
	  }

	//Input variables
	//===================================================================================================
	  Float_t dipho_mass         = 0.;
	  Float_t dipho_leadPt       = 0.;
	  Float_t dipho_leadEta      = 0.;
	  Float_t dipho_leadPhi      = 0.;
	  Float_t dipho_leadEt       = 0.;
	  Float_t dipho_leadIDMVA    = 0.;
	  Float_t dipho_lead_ptoM    = 0.;
          Float_t dipho_subleadPt    = 0.;
          Float_t dipho_subleadEta   = 0.;
          Float_t dipho_subleadPhi   = 0.;
          Float_t dipho_subleadEt    = 0.;
	  Float_t dipho_subleadIDMVA = 0.;
          Float_t dipho_sublead_ptoM = 0.;
	  Float_t dipho_mva          = 0.;
	  Float_t dijet_Mjj          = 0.;
	  Float_t dijet_LeadJPt      = 0.;
	  Float_t dijet_leadEta      = 0.;
	  Float_t dijet_leadPhi      = 0.;
	  Float_t dijet_LeadJMass    = 0.;
	  Float_t dijet_SubJPt       = 0.;
	  Float_t dijet_subleadEta   = 0.;
	  Float_t dijet_subleadPhi   = 0.;
	  Float_t dijet_SubJMass     = 0.;
	  Float_t dijet_abs_dEta     = 0.;
	  Float_t dijet_dphi         = 0.;
	  Float_t dijet_dPhi_trunc   = 0.;
          Float_t dijet_Zep          = 0.;
	  Float_t dijet_mva          = 0.;
	  Float_t dipho_dijet_MVA    = 0.;
	  Float_t metpt              = 0.;
	  Float_t metphi             = 0.;
	  Int_t   nvtx               = 0 ;
	  Float_t puweight           = 0.;
	  Float_t weight             = 0.;


	  for(int i=0;i<numberoffiles;i++){
	      mytrees[i] -> SetBranchAddress("dipho_mass"          ,  &dipho_mass          );	
	      mytrees[i] -> SetBranchAddress("dipho_leadPt"        ,  &dipho_leadPt        );	
	      mytrees[i] -> SetBranchAddress("dipho_leadEta"       ,  &dipho_leadEta       );	
	      mytrees[i] -> SetBranchAddress("dipho_leadPhi"       ,  &dipho_leadPhi       );	
	      mytrees[i] -> SetBranchAddress("dipho_leadEt"        ,  &dipho_leadEt        );	
	      mytrees[i] -> SetBranchAddress("dipho_leadIDMVA"     ,  &dipho_leadIDMVA     );	
	      mytrees[i] -> SetBranchAddress("dipho_lead_ptoM"     ,  &dipho_lead_ptoM     );	
	      mytrees[i] -> SetBranchAddress("dipho_subleadPt"     ,  &dipho_subleadPt     );	
	      mytrees[i] -> SetBranchAddress("dipho_subleadEta"    ,  &dipho_subleadEta    );	
	      mytrees[i] -> SetBranchAddress("dipho_subleadPhi"    ,  &dipho_subleadPhi    );	
	      mytrees[i] -> SetBranchAddress("dipho_subleadEt"     ,  &dipho_subleadEt     );	
	      mytrees[i] -> SetBranchAddress("dipho_subleadIDMVA"  ,  &dipho_subleadIDMVA  );	
	      mytrees[i] -> SetBranchAddress("dipho_sublead_ptoM"  ,  &dipho_sublead_ptoM  );	
	      mytrees[i] -> SetBranchAddress("dipho_mva"           ,  &dipho_mva           );	
	      mytrees[i] -> SetBranchAddress("dijet_Mjj"           ,  &dijet_Mjj           );	
	      mytrees[i] -> SetBranchAddress("dijet_LeadJPt"       ,  &dijet_LeadJPt       );	
	      mytrees[i] -> SetBranchAddress("dijet_leadEta"       ,  &dijet_leadEta       );	
	      mytrees[i] -> SetBranchAddress("dijet_leadPhi"       ,  &dijet_leadPhi       );	
	      mytrees[i] -> SetBranchAddress("dijet_LeadJMass"     ,  &dijet_LeadJMass     );	
	      mytrees[i] -> SetBranchAddress("dijet_SubJPt"        ,  &dijet_SubJPt        );	
	      mytrees[i] -> SetBranchAddress("dijet_subleadEta"    ,  &dijet_subleadEta    );	
	      mytrees[i] -> SetBranchAddress("dijet_subleadPhi"    ,  &dijet_subleadPhi    );	
	      mytrees[i] -> SetBranchAddress("dijet_SubJMass"      ,  &dijet_SubJMass      );	
	      mytrees[i] -> SetBranchAddress("dijet_abs_dEta"      ,  &dijet_abs_dEta      );	
	      mytrees[i] -> SetBranchAddress("dijet_dphi"          ,  &dijet_dphi          );	
	      mytrees[i] -> SetBranchAddress("dijet_dPhi_trunc"    ,  &dijet_dPhi_trunc    );	
	      mytrees[i] -> SetBranchAddress("dijet_Zep"           ,  &dijet_Zep           );	
	      mytrees[i] -> SetBranchAddress("dijet_mva"           ,  &dijet_mva           );	
	      mytrees[i] -> SetBranchAddress("dipho_dijet_MVA"     ,  &dipho_dijet_MVA     );	
	      mytrees[i] -> SetBranchAddress("metpt"               ,  &metpt               );	
	      mytrees[i] -> SetBranchAddress("metphi"              ,  &metphi              );	
	      mytrees[i] -> SetBranchAddress("nvtx"                ,  &nvtx                );	
	      mytrees[i] -> SetBranchAddress("puweight"            ,  &puweight            );	
	      mytrees[i] -> SetBranchAddress("weight"              ,  &weight              );	
	  }

        //Output Plots
        //==========================================================================================================================
	  TH1D* hMgg                 = new TH1D("hMgg"                  ,""  ,40  ,100.  ,180.  );  hMgg                 ->Sumw2();
	  TH1D* hlead_phoPt          = new TH1D("hlead_phoPt"           ,""  ,30  ,20.   ,260.  );  hlead_phoPt          ->Sumw2(); 
	  TH1D* hlead_phoEta         = new TH1D("hlead_phoEta"          ,""  ,30  ,-3.   ,3.    );  hlead_phoEta         ->Sumw2(); 
	  TH1D* hdipho_id1_mva       = new TH1D("hdipho_id1_mva"        ,""  ,40  ,-1.   ,1.    );  hdipho_id1_mva       ->Sumw2(); 
	  TH1D* hdipho_lead_ptoM     = new TH1D("hdipho_lead_ptoM"      ,""  ,40  ,0.    ,3.    );  hdipho_lead_ptoM     ->Sumw2(); 
	  TH1D* hsubl_phoPt          = new TH1D("hsubl_phoPt"           ,""  ,30  ,20.   ,140.  );  hsubl_phoPt          ->Sumw2(); 
	  TH1D* hsubl_phoEta         = new TH1D("hsubl_phoEta"          ,""  ,30  ,-3.   ,3.    );  hsubl_phoEta         ->Sumw2(); 
	  TH1D* hdipho_id2_mva       = new TH1D("hdipho_id2_mva"        ,""  ,40  ,-1.   ,1.    );  hdipho_id2_mva       ->Sumw2(); 
	  TH1D* hdipho_sublead_ptoM  = new TH1D("hdipho_sublead_ptoM"   ,""  ,40  ,0.    ,3.    );  hdipho_sublead_ptoM  ->Sumw2(); 
	  TH1D* hdipho_dEta          = new TH1D("hdipho_dEta"           ,""  ,40  ,0.    ,3.    );  hdipho_dEta          ->Sumw2(); 
	  TH1D* hdipho_dphi          = new TH1D("hdipho_dphi"           ,""  ,40  ,0.    ,3.2   );  hdipho_dphi          ->Sumw2(); 
	  TH1D* hdipho_mva           = new TH1D("hdipho_mva"            ,""  ,40  ,-1    ,1.    );  hdipho_mva           ->Sumw2(); 
	  TH1D* hMjj                 = new TH1D("hMjj"                  ,""  ,30  ,150.  ,3500. );  hMjj                 ->Sumw2(); 
	  TH1D* hlead_jetPt          = new TH1D("hlead_jetPt"           ,""  ,30  ,20.   ,290.  );  hlead_jetPt          ->Sumw2(); 
          TH1D* hlead_jetEta         = new TH1D("hlead_jetEta"          ,""  ,40  ,-5    ,5.    );  hlead_jetEta         ->Sumw2(); 
          TH1D* hsubl_jetPt          = new TH1D("hsubl_jetPt"           ,""  ,30  ,10.   ,160.  );  hsubl_jetPt          ->Sumw2(); 
          TH1D* hsubl_jetEta         = new TH1D("hsubl_jetEta"          ,""  ,40  ,-5.   ,5.    );  hsubl_jetEta         ->Sumw2(); 
          TH1D* hdijetDelEta         = new TH1D("hdijetDelEta"          ,""  ,30  ,2.    ,8.    );  hdijetDelEta         ->Sumw2(); 
          TH1D* hdijet_dphi          = new TH1D("hdijet_dphi"           ,""  ,40  ,0.    ,3.2   );  hdijet_dphi          ->Sumw2(); 
          TH1D* hdijet_Zep           = new TH1D("hdijet_Zep"            ,""  ,40  ,0.    ,4.    );  hdijet_Zep           ->Sumw2(); 
	  TH1D* hdijet_mva           = new TH1D("hdijet_mva"            ,""  ,20  ,0.4   ,1.    );  hdijet_mva           ->Sumw2(); 
	  TH1D* hdipho_dijet_mva     = new TH1D("hdipho_dijet_mva"      ,""  ,40  ,-0.2  ,1.    );  hdipho_dijet_mva     ->Sumw2(); 
	  TH1D* hMET                 = new TH1D("hMET"                  ,""  ,40  ,0.    ,250.  );  hMET                 ->Sumw2(); 
	  TH1D* hMET_phi             = new TH1D("hMET_phi"              ,""  ,40  ,-4.   ,4.    );  hMET_phi             ->Sumw2(); 
	  TH1D* hnvtx                = new TH1D("hnvtx"                 ,""  ,40  ,0.    ,40.   );  hnvtx                ->Sumw2(); 
	  TH1D* hMggjj               = new TH1D("hMggjj"                ,""  ,40  ,0.    ,3000. );  hMggjj               ->Sumw2(); 
	  TH1D* hdMggjjMjj           = new TH1D("hdMggjjMjj"            ,""  ,40  ,0.    ,1000. );  hdMggjjMjj           ->Sumw2(); 

        //Output Variables (filled into new trees)
        //============================================================================================
	  Float_t Mgg                = 0.;
	  Float_t BDT                = 0.;
	  Float_t puWgt              = 1.;
	  Float_t NormWgt            = 1.;
	  Float_t NormWgtplusMCw     = 1.;
	
   	//Loop each File
        //============================================================================================
      	  TFile* outfiles[numberoffiles];
	  TTree* outtree[numberoffiles];
	  for(int i=0;i<numberoffiles;i++){
              outfiles[i] = new TFile( outpath + "output_" + filenames[i] ,"RECREATE");

            //Create New Tree
            //==========================================================================================
              outtree[i]  = new TTree( "outTree" ,""); 
              outtree[i] -> Branch("Mgg"              ,&Mgg                 ,"Mgg/F"         );
              outtree[i] -> Branch("BDT"              ,&BDT                 ,"BDT/F"         );
              outtree[i] -> Branch("puWgt"            ,&puWgt               ,"puWgt/F"       );
              outtree[i] -> Branch("NormWgt"          ,&NormWgt             ,"NormWgt/F"     );
              outtree[i] -> Branch("NormWgtplusMCw"   ,&NormWgtplusMCw      ,"puWgt/F"       );


            //Dumper start
	    //==========================================================================================
              cout << filenames[i] << " start dumping  !!!" << endl;         
              for(int entry=0;entry<mytrees[i]->GetEntries();entry++){
                  mytrees[i]->GetEntry(entry);

	        //Preselection
	        //======================================================================================
	   	  if(dipho_leadPt<30 || dipho_subleadPt<20)                 continue;
                //Private Selection
                //======================================================================================
                  if( SideBand && i>1 ){
                     if(dipho_mass>120. && dipho_mass<130.) continue;
                  }

                   //Fill the Histograms and Set Weights
                   //======================================================================================
	             float MyWgt = puweight * norm[i];
                     if( MCweight && ( i==0 || i==1 ) ) MyWgt = weight*LUMI;
                    
                     hMgg                  ->Fill(  dipho_mass                            , MyWgt  ); 
                     hlead_phoPt           ->Fill(  dipho_leadPt                          , MyWgt  ); 
                     hlead_phoEta          ->Fill(  dipho_leadEta                         , MyWgt  ); 
                     hdipho_id1_mva        ->Fill(  dipho_leadIDMVA                       , MyWgt  ); 
                     hdipho_lead_ptoM      ->Fill(  dipho_lead_ptoM                       , MyWgt  ); 
                     hsubl_phoPt           ->Fill(  dipho_subleadPt                       , MyWgt  ); 
                     hsubl_phoEta          ->Fill(  dipho_subleadEta                      , MyWgt  ); 
                     hdipho_id2_mva        ->Fill(  dipho_subleadIDMVA                    , MyWgt  ); 
                     hdipho_sublead_ptoM   ->Fill(  dipho_sublead_ptoM                    , MyWgt  ); 
                     hdipho_dEta           ->Fill(  fabs(dipho_leadEta-dipho_subleadEta)  , MyWgt  ); 
                     hdipho_dphi           ->Fill(  fabs(dipho_leadPhi-dipho_subleadPhi)  , MyWgt  ); 
                     hdipho_mva            ->Fill(  dipho_mva                             , MyWgt  ); 
                     hMjj                  ->Fill(  dijet_Mjj                             , MyWgt  ); 
                     hlead_jetPt           ->Fill(  dijet_LeadJPt                         , MyWgt  ); 
                     hlead_jetEta          ->Fill(  dijet_leadEta                         , MyWgt  ); 
                     hsubl_jetPt           ->Fill(  dijet_SubJPt                          , MyWgt  ); 
                     hsubl_jetEta          ->Fill(  dijet_subleadEta                      , MyWgt  ); 
                     hdijetDelEta          ->Fill(  dijet_abs_dEta                        , MyWgt  ); 
                     hdijet_dphi           ->Fill(  dijet_dphi                            , MyWgt  ); 
                     hdijet_Zep            ->Fill(  dijet_Zep                             , MyWgt  ); 
                     hdijet_mva            ->Fill(  dijet_mva                             , MyWgt  ); 
                     hdipho_dijet_mva      ->Fill(  dipho_dijet_MVA                       , MyWgt  ); 
                     hMET                  ->Fill(  metpt                                 , MyWgt  ); 
                     hMET_phi              ->Fill(  metphi                                , MyWgt  ); 
                     hnvtx                 ->Fill(  nvtx                                  , MyWgt  );

	             TLorentzVector LeadphotonP4, subLeadphotonP4, diphotonP4;
	             LeadphotonP4.SetPtEtaPhiE( dipho_leadPt , dipho_leadEta , dipho_leadPhi , dipho_leadEt*cosh(dipho_leadEta));
	             subLeadphotonP4.SetPtEtaPhiE( dipho_subleadPt , dipho_subleadEta , dipho_subleadPhi , dipho_subleadEt*cosh(dipho_subleadEta));
	             diphotonP4 = LeadphotonP4 + subLeadphotonP4;
                    
	             TLorentzVector LeadjetP4, subLeadjetP4, dijetP4;
	             LeadjetP4.SetPtEtaPhiM( dijet_LeadJPt , dijet_leadEta , dijet_leadPhi , dijet_LeadJMass );
	             subLeadjetP4.SetPtEtaPhiM( dijet_SubJPt , dijet_subleadEta , dijet_subleadPhi , dijet_SubJMass );
	             dijetP4 = LeadjetP4 + subLeadjetP4;

	             hMggjj      ->  Fill((diphotonP4 + dijetP4).M()            , MyWgt );
	             hdMggjjMjj  ->  Fill((diphotonP4 + dijetP4).M()-dijetP4.M(), MyWgt );

                   //Fill into New tree
                   //=====================================================================================
	             Mgg            = dipho_mass          ;
	             BDT            = dijet_mva           ;
	             puWgt          = puweight            ;
	             NormWgt        = puweight * norm[i]  ;
	             NormWgtplusMCw = weight*LUMI         ;

                     outtree[i] -> Fill();
	      }//entry++
            //Dumper end
           
            //Write plots into the new file
            //============================================================================
              hMgg                 ->Write(); 
              hlead_phoPt          ->Write(); 
              hlead_phoEta         ->Write(); 
              hdipho_id1_mva       ->Write(); 
              hdipho_lead_ptoM     ->Write(); 
              hsubl_phoPt          ->Write(); 
              hsubl_phoEta         ->Write(); 
              hdipho_id2_mva       ->Write(); 
              hdipho_sublead_ptoM  ->Write(); 
              hdipho_dEta          ->Write(); 
              hdipho_dphi          ->Write(); 
              hdipho_mva           ->Write(); 
              hMjj                 ->Write(); 
              hlead_jetPt          ->Write(); 
              hlead_jetEta         ->Write(); 
              hsubl_jetPt          ->Write(); 
              hsubl_jetEta         ->Write(); 
              hdijetDelEta         ->Write(); 
              hdijet_dphi          ->Write(); 
              hdijet_Zep           ->Write(); 
              hdijet_mva           ->Write(); 
              hdipho_dijet_mva     ->Write(); 
              hMET                 ->Write(); 
              hMET_phi             ->Write(); 
              hnvtx                ->Write();
              hMggjj               ->Write(); 
              hdMggjjMjj           ->Write();

	    //Store New Files  
            //============================================================================          
	      outfiles[i] -> Write();
              outfiles[i] -> Close();
	      delete outfiles[i];


            //Plots reset 
            //============================================================================
	      hMgg                 ->Reset(); 
              hlead_phoPt          ->Reset(); 
              hlead_phoEta         ->Reset(); 
              hdipho_id1_mva       ->Reset(); 
              hdipho_lead_ptoM     ->Reset(); 
              hsubl_phoPt          ->Reset(); 
              hsubl_phoEta         ->Reset(); 
              hdipho_id2_mva       ->Reset(); 
              hdipho_sublead_ptoM  ->Reset(); 
              hdipho_dEta          ->Reset(); 
              hdipho_dphi          ->Reset(); 
              hdipho_mva           ->Reset(); 
              hMjj                 ->Reset(); 
              hlead_jetPt          ->Reset(); 
              hlead_jetEta         ->Reset(); 
              hsubl_jetPt          ->Reset(); 
              hsubl_jetEta         ->Reset(); 
              hdijetDelEta         ->Reset(); 
              hdijet_dphi          ->Reset(); 
              hdijet_Zep           ->Reset(); 
              hdijet_mva           ->Reset(); 
              hdipho_dijet_mva     ->Reset(); 
              hMET                 ->Reset(); 
              hMET_phi             ->Reset(); 
              hnvtx                ->Reset(); 
              hMggjj               ->Reset(); 
              hdMggjjMjj           ->Reset(); 

              cout << filenames[i] << " finishs  " << endl;        
	  }//i++
	  //Loop End
return 0;
}
