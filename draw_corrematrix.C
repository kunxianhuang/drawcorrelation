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
#include "PlotStyle.h"
#include <vector>

void help();
void draw_corrematrix(int argc, char* argv);
Double_t branchvalue[1000];
Double_t getmean(TTree *tree, Int_t bnum);
Double_t getrms(TTree *tree, Int_t bnum, Double_t bmean);
Double_t getXY(TTree *tree, Int_t bnumX, Int_t bnumY);


using namespace std;
void draw_corrematrix(int argc, char* argv[])
{
  if (argc<3){
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
  vector<vector<Double_t>> XYX;
  Double_t XY = 0.0;
  TString branchName;
  TString branchName2;
  Double_t bmean,brms;
  double *Dval; //declare the Double_t pointer
  Dval=(double*)malloc(nbranch*sizeof(double*)); //allocate memory
  memset(Dval, 0.0, nbranch*sizeof(double*)); //initialize each elements to be zeros
  //fill diagonal elements of correlation matrix

  for (Int_t i=0;i<nbranch;i++){
    dataTree->SetBranchAddress(tbra->At(i)->GetName(), &(branchvalue[i]));
  }
  
  for (Int_t ibra=0;ibra<nbranch;ibra++){
    //branchName= tbra->At(ibra)->GetName();
    //cout << ibra  << std::endl;
    bmean = getmean(dataTree,ibra);
    //cout << "???" << std::endl;
    brms = getrms(dataTree,ibra,bmean);
    //cout << ibra << " " << branchName << " mean is " << bmean <<std::endl;
    //cout << ibra << " " << branchName << "  rms is " << brms <<std::endl;

    (*corMat)(ibra,ibra) = 100.0*brms*brms/(brms*brms); //1.0*100%
    meanX.push_back(bmean);
    rmsX.push_back(brms);
    vector<Double_t> XYY;
    for (Int_t jbra=0;jbra<ibra;jbra++){
      //branchName2 = tbra->At(jbra)->GetName();
      XY = getXY(dataTree, ibra, jbra);
      XYY.push_back(XY);
      //cout << branchName << ", " << branchName2 << ": "<< XY <<std::endl;
      //cout << ibra << ", " << jbra << ": "<< XY <<std::endl;
    }
    XYX.push_back(XYY);
    //Set the branch to address

    branchName= tbra->At(ibra)->GetName();
    cout << ibra << ": " << branchName << std::endl;
  }
  //std::cout<<"meanX :"<<meanX.at(1)<< std::endl; 
  Double_t Xi;
  Double_t Yj;
  //fill off-diagonal elements of correlation matrix
  //loop over all data tree entries

  
  for (Int_t ibra=0;ibra<nbranch;ibra++){
    for (Int_t jbra=0;jbra<ibra;jbra++){
      (*corMat)(ibra,jbra) = 100.0*(  ( (XYX.at(ibra)).at(jbra)-meanX.at(ibra)*meanX.at(jbra) )/(rmsX.at(ibra)*rmsX.at(jbra))  );
      (*corMat)(jbra,ibra) = 100.0*(  ( (XYX.at(ibra)).at(jbra)-meanX.at(ibra)*meanX.at(jbra) )/(rmsX.at(ibra)*rmsX.at(jbra))  );
    }
  }

  /*
  cout<<"MeanX = "<<meanX.at(25)<<std::endl;
  cout<<"MeanY = "<<meanX.at(21)<<std::endl;
  cout<<" RMSX = "<<rmsX.at(25)<<std::endl;
  cout<<" RMSY = "<<rmsX.at(21)<<std::endl;
  cout<<" XY/N = "<< XY/dataTree->GetEntries()<<std::endl;
  cout<<"  ANS = "<< (*corMat)(25,21)<<std::endl;
  */

  
  char corre_Name_root[64];
  sprintf(corre_Name_root, "%s_corre.root", argv[2]);

  TFile *tfout = new TFile(corre_Name_root,"RECREATE");
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

  char corre_Name_pdf[64];
  char corre_Name_png[64];
  sprintf(corre_Name_pdf, "%s_correplot.pdf", argv[2]);
  sprintf(corre_Name_png, "%s_corre.png", argv[2]);
  c1->Print(corre_Name_pdf,".pdf");
  c1->Print(corre_Name_png,".png");
  
  hcovmat->Write();
  tfout->Close();
  return;
}

Double_t getmean(TTree *tree, Int_t bnum)
{
  Double_t bsum=0.0;
  Double_t bmean=0.0;
  for (Int_t iev;iev<tree->GetEntries();iev++){
    tree->GetEntry(iev);
    
    bmean += branchvalue[bnum]/tree->GetEntries();
    //cout << " value is " << branchvalue[bnum] <<std::endl;
    
  }
  
  //cout << " sum is " << bsum <<std::endl;
  //bmean = bsum/tree->GetEntries();
  //del histbt;
  return bmean;
}

Double_t getrms(TTree *tree, Int_t bnum, Double_t bmean)
{
  Double_t brms=0.0;
  Double_t bsqr=0.0;
  Double_t bmeansqr=0.0;

  for (Int_t iev;iev<tree->GetEntries();iev++){
    tree->GetEntry(iev);
    bmeansqr += branchvalue[bnum]*branchvalue[bnum]/tree->GetEntries();
    //cout << " value is " << branchvalue[bnum] <<std::endl;
  }
 
  //cout << " sqr is " << bsqr <<std::endl;
  //bmeansqr = bsqr/tree->GetEntries();
  //cout << " meansqr is " << bmeansqr <<std::endl;
  brms = TMath::Sqrt(bmeansqr-bmean*bmean);//
  //del histbt;
  return brms;
}

Double_t getXY(TTree *tree, Int_t bnumX, Int_t bnumY)
{
  Double_t bbXY=0.0;
  Double_t bbmeanXY=0.0;

  for (Int_t iev;iev<tree->GetEntries();iev++){
    tree->GetEntry(iev);
    bbXY += branchvalue[bnumX]*branchvalue[bnumY];
    //cout << " Xvalue is " << branchvalue[bnumX] <<std::endl;
    //cout << " Yvalue is " << branchvalue[bnumY] <<std::endl;
  }
  bbmeanXY = bbXY/tree->GetEntries();

  return bbmeanXY;
}

void help()
{
  printf("usage:draw_corrematrix rootfile treename outrootname.\n");
  printf("All branches should be Double_t.\n");
  return;
}

int main(int argc, char* argv[])
{
  PlotStyle();
  draw_corrematrix(argc,argv);
  return 0;
}
