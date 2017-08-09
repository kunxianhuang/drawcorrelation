//Draw the correlation matrix of input trees root file
//Written by K. Huang
//2017,08,07

#include "TH1F.h"
#include "TROOT.h"
#include "TMath.h"
#include "TTree.h"
#include "TArrayD.h"
#include "TStyle.h"
#include "TFile.h"
#include "TRandom.h"
#include "Riostream.h"
#include "TCanvas.h"
#include "TMatrixD.h"
#include "TH2F.h"
#include "TLegend.h"
#include "TBranch.h"
#include "TFile.h"
#include <vector>

void help();
void draw_corrematrix(int argc, char* argv);
Double_t getmean(TTree *tree, TString bname);
Double_t getrms(TTree *tree, TString bname, Double_t bmean);


using namespace std;
void draw_corrematrix(int argc, char* argv[])
{
  if (argc<4){
    help();
    exit(1);
  }
  
  TFile* treefile = new TFile(argv[1], "READ");
  if(!treefile){
    std::cout <<"Error opening file"<<argv[1]<<std::endl;
    return;
  }

  char tname[64];
  sprintf(tname, "%s", argv[2]);
  TTree *dataTree = (TTree*)treefile->Get(tname);
  if (!dataTree){
    std::cout<<"Error accessing Tree"<<argv[2]<<" in File "<<argv[1]<<std::endl;
    return;
  }else{dataTree->ls();}

  //Get information of branches in the TTree
  TObjArray *tbra = dataTree->GetListOfBranches(); //pointer to branches
  int nbranch = tbra->GetEntries(); //number of branches
  std::cout<<"Branch number is "<<nbranch<<std::endl;
  
  //vector to hold all information of tree
  
  
  //plot style
  TStyle *TStyle = gROOT->GetStyle("Plain"); // our style is based on Plain                                                  
  TStyle->SetOptStat(0);
  TStyle->SetPadTopMargin(0.05);
  TStyle->SetPadBottomMargin(0.21);
  TStyle->SetPadRightMargin(0.15);
  TStyle->SetPadLeftMargin(0.20);
  TStyle->SetPadGridX(0);
  TStyle->SetPadGridY(0);
  
  TStyle->SetOptTitle(0);
  TStyle->SetTitleW(.4);
  TStyle->SetTitleH(.10);
  TStyle->SetTitleX(.5);
  TStyle->SetTitleY(.9);
  TStyle->SetMarkerStyle(20);
  TStyle->SetMarkerSize(1.6);
  TStyle->cd();

  //create a correlation matrix with nbranchXnbranch elements
  TMatrixD* corMat = new TMatrixD( nbranch, nbranch);
  //initialize with zero
  for (Int_t ibra=0;ibra<nbranch;ibra++){
    for (Int_t jbra=0;jbra<nbranch;jbra++){
      (*corMat)(ibra,jbra) = 0.0;
    }
  }
  vector<Double_t> meanX;
  vector<Double_t> rmsX;
  TString branchName;
  Double_t bmean,brms;
  double *Dval; //declare the Double_t pointer
  Dval=(double*)malloc(nbranch*sizeof(double*)); //allocate memory
  memset(Dval, 0.0, nbranch*sizeof(double*)); //initialize each elements to be zeros
  //fill diagonal elements of correlation matrix
  for (Int_t ibra=0;ibra<nbranch;ibra++){
    branchName= tbra->At(ibra)->GetName();
    bmean = getmean(dataTree,branchName);
    brms = getrms(dataTree,branchName,bmean);
    (*corMat)(ibra,ibra) = 100.0*brms*brms/(brms*brms); //1.0*100%
    meanX.push_back(bmean);
    rmsX.push_back(brms);
    //Set the branch to address
    dataTree->SetBranchAddress(branchName, Dval+ibra);
  }
  //std::cout<<"meanX :"<<meanX.at(1)<< std::endl; 
  Double_t Xi;
  Double_t Yj;
  //fill off-diagonal elements of correlation matrix
  //loop over all data tree entries
  for (Int_t iev=0;iev<dataTree->GetEntries();iev++){
    dataTree->GetEntry(iev);
    
    if (iev%5000==0){
      std::cout<<"Read in "<<iev<<" events"<<std::endl;
      //std::cout<<*(Dval+1)<<std::endl;
    }							       
    for (Int_t ibra=0;ibra<nbranch;ibra++){
      for (Int_t jbra=0;jbra<ibra;jbra++){
	Xi = *(Dval+ibra);
	Yj = *(Dval+jbra);
	(*corMat)(ibra,jbra) += 100.0*((Xi*Yj-meanX.at(ibra)*meanX.at(jbra))/dataTree->GetEntries())/(rmsX.at(ibra)*rmsX.at(jbra));
	
	(*corMat)(jbra,ibra) += 100.0*((Xi*Yj-meanX.at(ibra)*meanX.at(jbra))/dataTree->GetEntries())/(rmsX.at(ibra)*rmsX.at(jbra));
      }
    }
  }
  TFile *tfout = new TFile(argv[3],"RECREATE");
  if(!tfout){
    std::cout <<"Error opening output file"<<argv[3]<<std::endl;
    return;
  }
  //Save into root file
  corMat->Write();
  //Draw correlation matrix plot
  TH2D *hcovmat = new TH2D("hcovmat","hcovmat",corMat->GetNcols(),corMat->GetColLwb(),1+corMat->GetColUpb(),corMat->GetNrows(),corMat->GetRowLwb(),1+corMat->GetRowUpb());
  //Set the bin contents
  Int_t ilow = corMat->GetRowLwb();
  Int_t iup  = corMat->GetRowUpb();
  Int_t jlow = corMat->GetColLwb();
  Int_t jup  = corMat->GetColUpb();
  for (Int_t i=ilow;i<=iup;i++) {
    for (Int_t j=jlow;j<=jup;j++) {
      hcovmat->SetBinContent(j-jlow+1,i-ilow+1,(*corMat)(i,j));
    }
  }
  //Set label of 2 axises
  for (Int_t ibin=1;ibin<nbranch+1;ibin++){
    hcovmat->GetXaxis()->SetBinLabel(ibin, tbra->At(ibin-1)->GetName());
    hcovmat->GetYaxis()->SetBinLabel(ibin, tbra->At(ibin-1)->GetName());
  }
  TCanvas *c1 = new TCanvas("c1","c1",600,600);
  hcovmat->LabelsOption("v"); //Xaxis(default) label vertical
  hcovmat->Draw("colz");
  c1->Print("corre_plot.pdf",".pdf");
  c1->Print("corre_plot.png",".png");
  
  hcovmat->Write();
  tfout->Close();
  return;
}

Double_t getmean(TTree *tree, TString bname)
{
  Double_t bmean=0.0;
  /*
  TString hist=">>histb";
  tree->Draw(bname+hist,"");
  TH1F *histbt = (TH1F*)gDirectory->Get("histb");
  bmean = histbt->GetMean();
  */
  Double_t val;
  tree->SetBranchAddress(bname, &val);
  for (Int_t iev;iev<tree->GetEntries();iev++){
    tree->GetEntry(iev);
    bmean += val*1.0/tree->GetEntries();
  }
  //del histbt;
  return bmean;
}

Double_t getrms(TTree *tree, TString bname, Double_t bmean)
{
  Double_t brms=0.0;
  /*
  TString hist=">>histb";
  tree->Draw(bname+hist,"");
  TH1F *histbt = (TH1F*)gDirectory->Get("histb");
  brms = histbt->GetRMS();
  */
  Double_t val;
  Double_t bmeansqr=0.0;
  tree->SetBranchAddress(bname, &val);
  for (Int_t iev;iev<tree->GetEntries();iev++){
    tree->GetEntry(iev);
    bmeansqr+= val*val/tree->GetEntries();
  }

  brms = TMath::Sqrt(bmeansqr-bmean);
  //del histbt;
  return brms;
}

void help()
{
  printf("usage:draw_corrematrix rootfile treename outrootname.\n");
  printf("All branches should be Double_t.\n");
  return;
}

int main(int argc, char* argv[])
{
  draw_corrematrix(argc,argv);
  return 0;
}
