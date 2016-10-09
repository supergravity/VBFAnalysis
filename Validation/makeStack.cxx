#include <iostream>

#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TH1D.h"
#include "THStack.h"
#include "TLatex.h"
#include "TLegend.h"
#include "TLine.h"

#ifndef __ROOTLOGON__
#define __ROOTLOGON__
#include "macro/rootlogon.C"
#endif

#define MH 125
#define LUMI 12.889

using namespace std;

int main(){

	//Option
	//============================================================================
          bool SetLogScale = false;	
          bool AddSignalMC = true;

	//Input and Output Path  
	//============================================================================
          TString inpath = "output/";
          TString outpath = "result/";

	  system("mkdir -p " + outpath);

	//Input ROOT Files
	//==========================================================================================================
          const int N_infiles = 10;
          TString infilename[N_infiles];
          infilename[0] = "output_VBFHToGG_M125_13TeV_amcatnlo_pythia8.root"                                    ;
          infilename[1] = "output_GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root"                             ;
          infilename[2] = "output_GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8.root"  ;
          infilename[3] = "output_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root"  ;
          infilename[4] = "output_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root" ;
          infilename[5] = "output_DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root"                                ;
          infilename[6] = "output_QCD_Pt-30to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root"   ;
          infilename[7] = "output_QCD_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root"  ;
          infilename[8] = "output_QCD_Pt-30toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8.root"   ;
          infilename[9] = "output_Run2016BCD_ICHEP_PromptReco_v2.root"                                          ;
	

	//Input Plots Information
	//==================================================================================================
	//----------------------------------------------------------
	//NOTE::The first plot has to be contral plot.Here is hMgg.
	//----------------------------------------------------------
          const int N_plots = 27;
          TString plotname[N_plots];
          TString xTitlename[N_plots];
          plotname[0]  = "hMgg"                ;  xTitlename[0]  = "M_{#gamma#gamma} (GeV)"          ; 
          plotname[1]  = "hlead_phoPt"         ;  xTitlename[1]  = "Pt_{#gamma 1} (GeV)"             ;
          plotname[2]  = "hlead_phoEta"        ;  xTitlename[2]  = "#eta_{#gamma 1}"                 ;
          plotname[3]  = "hdipho_id1_mva"      ;  xTitlename[3]  = "Photon1 ID MVA"                  ;
          plotname[4]  = "hdipho_lead_ptoM"    ;  xTitlename[4]  = "Pt_{#gamma 1}/M_{#gamma#gamma}"  ;
          plotname[5]  = "hsubl_phoPt"         ;  xTitlename[5]  = "Pt_{#gamma 2} (GeV)"             ;
          plotname[6]  = "hsubl_phoEta"        ;  xTitlename[6]  = "#eta_{#gamma 2}"                 ;
          plotname[7]  = "hdipho_id2_mva"      ;  xTitlename[7]  = "Photon2 ID MVA"                  ;
          plotname[8]  = "hdipho_sublead_ptoM" ;  xTitlename[8]  = "Pt_{#gamma 2}/M_{#gamma#gamma}"  ;
          plotname[9]  = "hdipho_dEta"         ;  xTitlename[9]  = "#Delta#eta(#gamma#gamma)"        ;
          plotname[10] = "hdipho_dphi"         ;  xTitlename[10] = "#Delta#phi(#gamma#gamma)"        ;
          plotname[11] = "hdipho_mva"          ;  xTitlename[11] = "diphoton MVA"                    ;
          plotname[12] = "hMjj"                ;  xTitlename[12] = "M_{jj} (GeV)"                    ;
          plotname[13] = "hlead_jetPt"         ;  xTitlename[13] = "Pt_{jet 1} (GeV)"                ;
          plotname[14] = "hlead_jetEta"        ;  xTitlename[14] = "#eta_{jet 1}"                    ;
          plotname[15] = "hsubl_jetPt"         ;  xTitlename[15] = "Pt_{jet 2} (GeV)"                ;
          plotname[16] = "hsubl_jetEta"        ;  xTitlename[16] = "#eta_{jet 2}"                    ;
          plotname[17] = "hdijetDelEta"        ;  xTitlename[17] = "#Delta#eta(jj)"                  ;
          plotname[18] = "hdijet_dphi"         ;  xTitlename[18] = "#Delta#phi(jj)"                  ;
          plotname[19] = "hdijet_Zep"          ;  xTitlename[19] = "Zeppenfeld"                      ;
          plotname[20] = "hdijet_mva"          ;  xTitlename[20] = "dijet BDT"                       ;
          plotname[21] = "hdipho_dijet_mva"    ;  xTitlename[21] = "combined MVA"                    ;
          plotname[22] = "hMET"                ;  xTitlename[22] = "MET"                             ;
          plotname[23] = "hMET_phi"            ;  xTitlename[23] = "MET_Eta"                         ;
          plotname[24] = "hnvtx"               ;  xTitlename[24] = "nvtx"                            ;
          plotname[25] = "hMggjj"              ;  xTitlename[25] = "M_{#gamma#gammajj}"              ;
          plotname[26] = "hdMggjjMjj"          ;  xTitlename[26] = "M_{#gamma#gammajj}-M_{jj}"       ;

	//Start To Make Stack Plots
	//============================================================================================ 
          rootlogon();
     
          TFile* infile[N_infiles];
          TH1D* histo[N_plots][N_infiles];
          TH1D* hVBF[N_plots];
          TH1D* hGGF[N_plots];
          TH1D* hGJet[N_plots];
          TH1D* hdipho[N_plots];
          TH1D* hQCD[N_plots];
          TH1D* hCont[N_plots];
          TH1D* hdata[N_plots];
          TH1D* hdataClone[N_plots];

          TCanvas* canv[N_plots];
          TPad* padUp[N_plots];
          TPad* padDown[N_plots];
          THStack* hMCStack[N_plots];
          TLegend* leg[N_plots];
          TLatex* latex[N_plots];
          TLine* ratioLine[N_plots];

          double scale_factor = 1;	

          for(int i=0;i<N_plots;i++){
              for(int j=0;j<N_infiles;j++){
                  infile[j] = TFile::Open( inpath + infilename[j]);
                  histo[i][j] = (TH1D*)infile[j] -> Get( plotname[i] );
              }
              hVBF[i]  = (TH1D*)histo[i][0]->Clone();
              hGGF[i]  = (TH1D*)histo[i][1]->Clone();
              hGJet[i] = (TH1D*)histo[i][2]->Clone();
              hGJet[i]->Add(histo[i][3]);
              hGJet[i]->Add(histo[i][4]);
              hdipho[i]= (TH1D*)histo[i][5]->Clone();
              hQCD[i]  = (TH1D*)histo[i][6]->Clone();
              hQCD[i]->Add(histo[i][7]);
              hQCD[i]->Add(histo[i][8]);

              hCont[i] = (TH1D*)hGJet[i]->Clone();
              hCont[i]->Add(hdipho[i]);
              hCont[i]->Add(hQCD[i]);
              hdata[i] = (TH1D*)histo[i][9]->Clone();
              
              if(i==0){
		 double VBFpercent = (hVBF[i]->Integral()/(hVBF[i]->Integral()+hGGF[i]->Integral()))*100;
		 double GGFpercent = 100 - VBFpercent; 
		 cout << "------------------------------------------------------------------------------\n"
		      << "VBF = " << hVBF[i]->Integral() << "(" << VBFpercent << ")" << "\n"
		      << "GGF = " << hGGF[i]->Integral() << "(" << GGFpercent << ")" << "\n"
		      << "------------------------------------------------------------------------------"
		      <<endl;
                 int minbin = hCont[i]->FindBin(120.);
                 int maxbin = hCont[i]->FindBin(130.);
                 double NCont = hCont[i]->Integral() - hCont[i]->Integral(minbin,maxbin);
                 double Ndata = hdata[i]->Integral() - hdata[i]->Integral(minbin,maxbin);
                 scale_factor = Ndata/NCont;
              }

              hGJet[i] ->Scale(scale_factor);
              hdipho[i]->Scale(scale_factor);
              hQCD[i]  ->Scale(scale_factor);
              hCont[i] ->Scale(scale_factor);

              canv[i] = new TCanvas(Form("canv%d",i),"",600,650);
              canv[i]->cd();
              padUp[i] = new TPad(Form("padUp%d",i),"",0.,0.24,1.,0.98);
              padUp[i] -> SetTopMargin(0.05);
              padUp[i] -> SetBottomMargin(0.019);
              padUp[i] -> Draw();
              padUp[i] -> cd();
              
              hMCStack[i] = new THStack(Form("hMCStack%d",i),"");
              hVBF[i]   -> SetLineColor(kRed);             
              hVBF[i]   -> SetLineWidth(2);
              hGGF[i]   -> SetLineColor(kYellow);
              hGGF[i]   -> SetLineWidth(2);
              hGJet[i]  -> SetFillColor(kGreen);
              hGJet[i]  -> SetLineColor(kBlack);
              hdipho[i] -> SetFillColor(kBlue-4);
              hdipho[i] -> SetLineColor(kBlack);
              hQCD[i]   -> SetFillColor(kOrange+10);
              hMCStack[i]->Add(hGJet[i]);
              hMCStack[i]->Add(hdipho[i]);
              hMCStack[i]->Add(hQCD[i]);
              hMCStack[i] -> Draw("histo");
              hdata[i] -> SetLineColor(kBlack);
              hdata[i] -> SetMarkerSize(1.);
              hdata[i] -> SetMarkerStyle(20);
              hdata[i] -> Draw("E1same");
              float binM = hdata[i] -> GetBinWidth(1);
              hMCStack[i] -> GetXaxis()->SetLabelSize(0.);
              hMCStack[i] -> GetYaxis()->SetTitle(Form("Events/(%.2f)",binM));

              if(SetLogScale){
                 hMCStack[i] -> SetMinimum(0.01);     
                 hMCStack[i] -> SetMaximum(1000*(hdata[i]->GetMaximum()));
                 hVBF[i] -> Scale(20);
                 hGGF[i] -> Scale(0.1);
                 padUp[i] -> SetLogy();
              }else{
                 hMCStack[i] -> SetMinimum(0.);     
                 hMCStack[i] -> SetMaximum(1.4*(hdata[i]->GetMaximum()));
              }
              if(AddSignalMC){
                 hVBF[i] -> Draw("histosame");     
                 hGGF[i] -> Draw("histosame");     

                 leg[i] = new TLegend(0.6, 0.7, 0.9, 0.92);
                 if(SetLogScale){
                    leg[i] -> AddEntry(hVBF[i],Form("VBF(mH = %dGeV) x20",MH),"L"); 
                    leg[i] -> AddEntry(hGGF[i],Form("GGF(mH = %dGeV) /10",MH),"L"); 
                 }else{
                    leg[i] -> AddEntry(hVBF[i],Form("VBF(mH = %dGeV)",MH),"L");
                    leg[i] -> AddEntry(hGGF[i],Form("GGF(mH = %dGeV)",MH),"L");
                 }
              }else{
                 leg[i] = new TLegend(0.6, 0.75, 0.9, 0.94);     
              }

              leg[i] -> AddEntry(hGJet[i]    ,"#gamma Jet"   ,"F"); 
              leg[i] -> AddEntry(hdipho[i]   ,"#gamma #gamma","F"); 
              leg[i] -> AddEntry(hQCD[i]     ,"QCD"          ,"F"); 
              leg[i] -> AddEntry(hdata[i]    ,"Data"         ,"PL");
              leg[i] -> SetFillStyle(0);
              leg[i] -> SetBorderSize(0);
              leg[i] -> Draw();   

              latex[i] = new TLatex();
              latex[i] -> SetNDC();
              latex[i] -> SetTextFont(62);
              latex[i] -> SetTextSize(0.055);
              latex[i] -> DrawText(0.12,0.96,"CMS");
              latex[i] -> SetTextFont(42);
              latex[i] -> SetTextSize(0.045);
              latex[i] -> DrawText(0.23,0.96,"Preliminary");
              latex[i] -> SetTextSize(0.04);
              latex[i] -> DrawLatex(0.6,0.96,Form("#sqrt{s}=13 TeV, L=%.3f fb^{-1}",LUMI));
              latex[i] -> SetTextSize(0.035);
              latex[i] -> DrawLatex(0.17,0.88,"CMSSW 80X");
              latex[i] -> DrawLatex(0.17,0.835,"Dijet BDT > 0.4");
              latex[i] -> DrawLatex(0.17,0.795,"Normalized to SB");

              canv[i] -> Update();
              canv[i] ->cd();
              padDown[i] = new TPad("padDown","",0.,0.02,1.,0.25);
              padDown[i] -> SetTopMargin(0.0);
              padDown[i] -> SetBottomMargin(0.35);
              padDown[i] -> Draw();
              padDown[i] -> cd();

              hdataClone[i] = (TH1D*)hdata[i] -> Clone();
              hdataClone[i] -> GetXaxis()->SetTitleSize(0.15);
              hdataClone[i] -> GetXaxis()->SetLabelSize(0.15);
              hdataClone[i] -> GetYaxis()->SetTitleSize(0.15);
              hdataClone[i] -> GetYaxis()->SetLabelSize(0.15); 
              hdataClone[i] -> GetYaxis()->SetTitleOffset(0.35);
              hdataClone[i] -> GetYaxis()->SetNdivisions(905);
              hdataClone[i] -> SetLineColor(kBlack);
              hdataClone[i] -> SetXTitle(xTitlename[i]);
              hdataClone[i] -> SetYTitle("Data/MC");
              hdataClone[i] -> Divide(hdataClone[i],hCont[i],1.,1.);
              hdataClone[i] -> SetMinimum(-0.5);
              hdataClone[i] -> SetMaximum(2.5);
              hdataClone[i] -> Draw("E1same");

              ratioLine[i] = new TLine(hdataClone[i]->GetBinLowEdge(1),1, hdataClone[i]->GetBinLowEdge(hdataClone[i]->GetNbinsX()+1),1);
              ratioLine[i] -> SetLineColor(kBlue);
              ratioLine[i] -> SetLineStyle(2);
              ratioLine[i] -> SetLineWidth(5);
              ratioLine[i] -> Draw();
              hdataClone[i] -> Draw("E1same");

              canv[i] -> Update();
              canv[i] -> Print( outpath + plotname[i] + ".pdf");
              canv[i] -> Close();

              delete canv[i];              
          }
	//End
	
return 0;
}

