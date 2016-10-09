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
#include "../macro/rootlogon.C"
#endif

#include "../interface/makePlot.h"

using namespace std;

makePlot::makePlot( map<string,string> infile, string outdir ):
	_infile(infile),
	_outdir(outdir)
{
}
makePlot::~makePlot()
{
}

void makePlot::makeStackPlot(std::string plotname, string Xaxisname,bool SetLogScale, bool AddSignalMC, bool NormToData = true){
      
      //gROOT->LoadMacro("../macro/rootlogon.C");
      rootlogon();

      map<string,TH1D*> compPlot;	
      for(map<string,string>::iterator it = _infile.begin();it!= _infile.end();++it){

	  TFile*inputfile = new TFile((it->first).c_str());
	  compPlot[it->second] = (TH1D*)inputfile->Get( plotname.c_str() );
      }
      TH1D* hVBF_125 = (TH1D*)compPlot["vbf"]  -> Clone();
      TH1D* hGGF_125 = (TH1D*)compPlot["ggf"]  -> Clone();
      TH1D* hData    = (TH1D*)compPlot["data"] -> Clone();
      int Nbin = hData->GetNbinsX();
      double Xmin = hData->GetXaxis()->GetXmin();
      double Xmax = hData->GetXaxis()->GetXmax();
      TH1D*hGammaJet = new TH1D("hGammaJet","",Nbin,Xmin,Xmax); 
      TH1D*hDipho    = new TH1D("hDipho"   ,"",Nbin,Xmin,Xmax); 
      TH1D*hQCD      = new TH1D("hQCD"     ,"",Nbin,Xmin,Xmax);
      for(map<string,TH1D*>::iterator it = compPlot.begin();it!= compPlot.end();++it){
         
	  string str  = (it->first).substr(0,((it->first).find_last_of("_")));
	  if(str == "gj"    ) hGammaJet -> Add(it->second);
	  if(str == "dipho" ) hDipho    -> Add(it->second);
	  if(str == "qcd"   ) hQCD      -> Add(it->second);
      }
      TH1D* hContinuum = (TH1D*)hGammaJet -> Clone();
            hContinuum -> Add(hDipho);
            hContinuum -> Add(hQCD)  ;
      if(!(hContinuum->Integral())){
	 cout << "No background files, please check your input files"  << endl;
	 exit(1);
      }
   
      if(NormToData){
	 double scale_factor = hData->Integral()/hContinuum->Integral();
	 hGammaJet   -> Scale(scale_factor);
	 hDipho      -> Scale(scale_factor);
	 hQCD        -> Scale(scale_factor);
	 hContinuum  -> Scale(scale_factor);
      }
//=========================================================================================================
      TCanvas* canv = new TCanvas("canv","",600,650); 
      canv -> cd();
      TPad* padup   = new TPad("padup","",0.,0.24,1.,0.98);
      padup -> SetTopMargin(0.05);
      padup -> SetBottomMargin(0.019);
      padup -> Draw();
      if(SetLogScale) padup -> SetLogy();
      padup ->cd();

      THStack* myHStack = new THStack("myHStack","myHStack");
      hVBF_125  -> SetLineColor(kRed);
      hVBF_125  -> SetLineWidth(2);
      hGGF_125  -> SetLineColor(kYellow);
      hGGF_125  -> SetLineWidth(2);
      hData     -> SetLineColor(kBlack);
      hGammaJet -> SetFillColor(kGreen);
      hGammaJet -> SetLineColor(kBlack);
      hDipho    -> SetFillColor(kBlue-4);
      hDipho    -> SetLineColor(kBlack);
      hQCD      -> SetFillColor(kOrange+10);
      hQCD      -> SetLineColor(kBlack);
      myHStack -> Add(hGammaJet);
      myHStack -> Add(hDipho);
      myHStack -> Add(hQCD);
      myHStack -> Draw("Histo");
      
      if(SetLogScale){
	 myHStack -> SetMinimum(0.01);     
	 myHStack -> SetMaximum(1000*(hData->GetMaximum()));
	 hVBF_125 -> Scale(20);
	 hGGF_125 -> Scale(0.1);
      }else{
	 myHStack -> SetMinimum(0.);     
	 myHStack -> SetMaximum(1.4*(hData->GetMaximum()));
      }
      if(AddSignalMC){
	 hVBF_125 -> Draw("histosame");     
	 hGGF_125 -> Draw("histosame");     
      }
      hData -> SetMarkerSize(1.);
      hData -> SetMarkerStyle(20);
      hData -> Draw("E1same");
      //canv  -> Update();
      float binM = hData -> GetBinWidth(1);
      myHStack -> GetXaxis()->SetLabelSize(0.);
      myHStack -> GetYaxis()->SetTitle(Form("Events/(%.2f)",binM));

      TLatex* latex = new TLatex();
      latex -> SetNDC();
      latex -> SetTextFont(62);
      latex -> SetTextSize(0.055);
      latex -> DrawText(0.12,0.96,"CMS");
      latex -> SetTextFont(42);
      latex -> SetTextSize(0.045);
      latex -> DrawText(0.23,0.96,"Preliminary");
      latex -> SetTextSize(0.04);
      latex -> DrawLatex(0.6,0.96,"#sqrt{s}=13 TeV, L=12.887 fb^{-1}");
      latex -> SetTextSize(0.035);
      latex -> DrawLatex(0.17,0.88,"CMSSW 80X");
      latex -> DrawLatex(0.17,0.835,"Dijet BDT > 0.4");
      latex -> DrawLatex(0.17,0.795,"Normalized to SB");

      TLegend* leg;
      if(AddSignalMC){
	 leg = new TLegend(0.6, 0.7, 0.9, 0.92);
	 if(SetLogScale){
            leg -> AddEntry(hVBF_125,"VBF(mH = 125GeV) x20","L"); 
            leg -> AddEntry(hGGF_125,"GGF(mH = 125GeV) /10","L"); 
	 }else{
            leg -> AddEntry(hVBF_125,"VBF(mH = 125GeV)","L"); 
            leg -> AddEntry(hGGF_125,"GGF(mH = 125GeV)","L"); 
	 }
      }else{
	 leg = new TLegend(0.6, 0.75, 0.9, 0.94);	      
      }
      leg -> AddEntry(hGammaJet,"#gamma Jet"   ,"F"); 
      leg -> AddEntry(hDipho   ,"#gamma #gamma","F"); 
      leg -> AddEntry(hQCD     ,"QCD"          ,"F"); 
      leg -> AddEntry(hData    ,"Data"         ,"PL"); 
      leg -> SetFillStyle(0);
      leg -> SetBorderSize(0);
      leg -> Draw();
      
      canv -> Update();
      canv ->cd();
      TPad* padDown = new TPad("padDown","",0.,0.02,1.,0.25);
      padDown -> SetTopMargin(0.0);
      padDown -> SetBottomMargin(0.31);
      padDown -> Draw();
      padDown -> cd();

      TH1D* hDataClone = (TH1D*)hData -> Clone();
      hDataClone -> GetXaxis()->SetTitleSize(0.15);
      hDataClone -> GetXaxis()->SetLabelSize(0.15);
      hDataClone -> GetYaxis()->SetTitleSize(0.15);
      hDataClone -> GetYaxis()->SetLabelSize(0.15); 
      hDataClone -> GetYaxis()->SetTitleOffset(0.35);
      hDataClone -> GetYaxis()->SetNdivisions(905);
      hDataClone -> SetLineColor(kBlack);
      hDataClone -> SetXTitle(Xaxisname.c_str());
      hDataClone -> SetYTitle("Data/MC");

      hDataClone -> Divide(hDataClone,hContinuum,1.,1.);
      hDataClone -> SetMinimum(-1.);
      hDataClone -> SetMaximum(3.);
      hDataClone -> Draw("E1same");

      TLine* ratioLine = new TLine(hDataClone->GetBinLowEdge(1),1, hDataClone->GetBinLowEdge(hDataClone->GetNbinsX()+1),1);
      ratioLine -> SetLineColor(kBlue);
      ratioLine -> SetLineStyle(2);
      ratioLine -> SetLineWidth(5);
      ratioLine -> Draw();
      hDataClone -> Draw("E1same");

      canv -> Update();
      canv -> Print(Form("%s/%s.pdf",_outdir.c_str(),plotname.c_str()));
      canv -> Close();

      delete canv;

}
