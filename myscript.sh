#!/bin/bash

datapath="/wk_cms/youying/public/RunIISpring16DR80X-2_2_0-25ns_ICHEP16_MiniAODv2"


./bin/vbf_analysis -i $datapath/VBFHToGG_M125_13TeV_amcatnlo_pythia8.root,$datapath/GluGluHToGG_M125_13TeV_amcatnloFXFX_pythia8.root,$datapath/DiPhotonJetsBox_MGG-80toInf_13TeV-Sherpa.root,$datapath/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root,$datapath/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8.root,$datapath/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root,$datapath/Run2016BCD_ICHEP_PromptReco_v2.root -d /wk_cms/youying/build2/vbfinfo.dat --LUMI 12.887 --SideBand --AddSignal --NormToData

