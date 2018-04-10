# drawcorrelation

ROOT use TTree object to restore data of each events.But there is no easy function to draw correction matrix for ntuple-like TTree data. I wrote a C++ file to read a root Tree file with all variables are type of Double_t, then draw a correlation matrix plot and save into a root file in format of TH2D.
```bash
usage:./drawcorrelation [inputfile] [TTree name] [outputfile]
```
