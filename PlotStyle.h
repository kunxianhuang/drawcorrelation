void PlotStyle()
{
  TStyle *SumanStyle;
  SumanStyle  = new TStyle("SumanStyle","My Root Styles");
 
  const Int_t NCont = 100;
  const Int_t NRGBs = 5;

/*   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 }; // Original */
/*   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 }; */
/*   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 }; */
/*   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };     */

  Double_t stops[NRGBs] = { 0.20, 0.50, 0.60, 0.75, 1.00 }; // First Mod
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.90, 1.00, 0.50 };
  Double_t green[NRGBs] = { 0.40, 0.80, 1.00, 0.15, 0.00 };
  Double_t blue[NRGBs]  = { 0.50, 1.00, 0.10, 0.20, 0.00 };

  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  SumanStyle->SetNumberContours(NCont);

  SumanStyle->SetCanvasBorderMode(0); // Canvas
  SumanStyle->SetCanvasBorderSize(0);
  SumanStyle->SetCanvasColor(0);
 
  SumanStyle->SetPadBorderMode(0); // Pad 
  SumanStyle->SetPadColor(0);
  SumanStyle->SetFrameFillColor(0); 

  SumanStyle->SetOptTitle(0);
  SumanStyle->SetPadRightMargin(0.16);  // Make  more room for X and Y titles
  SumanStyle->SetPadLeftMargin(0.16);
  SumanStyle->SetPadBottomMargin(0.16);
  SumanStyle->SetPadTopMargin(0.16); // Default Values are 0.16

  SumanStyle->SetLabelFont(132,"XYZ");  // Graphs
  SumanStyle->SetLabelSize(0.05,"XYZ");
  SumanStyle->SetLabelOffset(0.01,"XYZ");
  SumanStyle->SetTitleFont(132,"XYZ");
  SumanStyle->SetTitleSize(0.06,"XYZ");// Original
  SumanStyle->SetTitleOffset(1.0,"XYZ");// Original
 
  SumanStyle->SetFrameBorderMode(0); // Frames
  SumanStyle->SetFrameBorderSize(0);
 
  SumanStyle->SetErrorX(0); // Graphs
  SumanStyle->SetMarkerStyle(20);
 
  SumanStyle->SetOptStat(0);  // Stats
  // SumanStyle->SetOptStat(1);  // Stats
  // SumanStyle->SetOptFit(1110);
  SumanStyle->SetOptFit(0000);
  SumanStyle->SetStatY(0.84);
  SumanStyle->SetStatX(0.84);
  SumanStyle->SetStatW(0.15);
  SumanStyle->SetStatH(0.12);
  SumanStyle->SetStatColor(0);
  SumanStyle->SetStatBorderSize(0);

  //TMathText l;  //For proper math texts
   //l.SetTextSize(0.013);
   //l.SetTextFont(132);
   //l.SetTextAlign(23);

 
  gROOT->SetStyle("SumanStyle");      
}

void AltPlotStyle()
{
  TStyle *SumanStyle;
  SumanStyle  = new TStyle("SumanStyle","My Root Styles");
 
  const Int_t NCont = 100;
  const Int_t NRGBs = 5;

/*   Double_t stops[NRGBs] = { 0.00, 0.34, 0.61, 0.84, 1.00 }; // Original */
/*   Double_t red[NRGBs]   = { 0.00, 0.00, 0.87, 1.00, 0.51 }; */
/*   Double_t green[NRGBs] = { 0.00, 0.81, 1.00, 0.20, 0.00 }; */
/*   Double_t blue[NRGBs]  = { 0.51, 1.00, 0.12, 0.00, 0.00 };     */

  Double_t stops[NRGBs] = { 0.20, 0.50, 0.60, 0.75, 1.00 }; // First Mod
  Double_t red[NRGBs]   = { 0.00, 0.00, 0.90, 1.00, 0.50 };
  Double_t green[NRGBs] = { 0.40, 0.80, 1.00, 0.15, 0.00 };
  Double_t blue[NRGBs]  = { 0.50, 1.00, 0.10, 0.20, 0.00 };

  TColor::CreateGradientColorTable(NRGBs, stops, red, green, blue, NCont);
  SumanStyle->SetNumberContours(NCont);

  SumanStyle->SetCanvasBorderMode(0); // Canvas
  SumanStyle->SetCanvasBorderSize(0);
  SumanStyle->SetCanvasColor(kWhite);
 
  SumanStyle->SetPadBorderMode(0); // Pad 
  SumanStyle->SetPadColor(kWhite);

  /* SumanStyle->SetOptTitle(0);  */
  /* SumanStyle->SetPadRightMargin(0.16);  // Make  more room for X and Y titles  */
  /* SumanStyle->SetPadLeftMargin(0.16);    */
  /* SumanStyle->SetPadBottomMargin(0.16); */
  /* SumanStyle->SetPadTopMargin(0.16); // Default Values are 0.16 */

  /* SumanStyle->SetLabelFont(132,"XYZ");  // Graphs  */
  /* SumanStyle->SetLabelSize(0.05,"XYZ"); */
  /* SumanStyle->SetLabelOffset(0.01,"XYZ"); */
  /* SumanStyle->SetTitleFont(132,"XYZ");  */
  /* SumanStyle->SetTitleSize(0.06,"XYZ");// Original */
  /* SumanStyle->SetTitleOffset(1.0,"XYZ");// Original */
 
 SumanStyle->SetOptTitle(0); 
  SumanStyle->SetPadRightMargin(0.0);  // Make  more room for X and Y titles 
  SumanStyle->SetPadLeftMargin(0.0);   
  SumanStyle->SetPadBottomMargin(0.0);
  SumanStyle->SetPadTopMargin(0.0); // Default Values are 0.16


SumanStyle->SetLabelFont(132,"XYZ");  
  SumanStyle->SetLabelSize(0.00,"XYZ");
  SumanStyle->SetLabelOffset(0.00,"XYZ");
  SumanStyle->SetTitleFont(132,"XYZ");
  SumanStyle->SetTitleSize(0.00,"XYZ");
  SumanStyle->SetTitleOffset(0.0,"XYZ");


 
  SumanStyle->SetFrameBorderMode(0); // Frames
  SumanStyle->SetFrameBorderSize(0);
 
  SumanStyle->SetErrorX(0); // Graphs
  SumanStyle->SetMarkerStyle(20);
 
  SumanStyle->SetOptStat(0);  // Stats
  // SumanStyle->SetOptStat(1);  // Stats
  // SumanStyle->SetOptFit(1110);
  SumanStyle->SetOptFit(0000);
  SumanStyle->SetStatY(0.84);
  SumanStyle->SetStatX(0.84);
  SumanStyle->SetStatW(0.15);
  SumanStyle->SetStatH(0.12);
  SumanStyle->SetStatColor(0);
  SumanStyle->SetStatBorderSize(0);
  
  gROOT->SetStyle("SumanStyle");      
}
