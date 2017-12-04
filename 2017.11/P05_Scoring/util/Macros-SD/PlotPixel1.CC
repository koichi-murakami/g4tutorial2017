{
gROOT->Reset();
TFile *f = TFile::Open("Pixel.root");
TCanvas * Pixel = new TCanvas("Pixel", "Energy Deposit");

TH1D * sum = (TH1D*)f->Get("h1:2");
sum->Draw("HIST");

}

