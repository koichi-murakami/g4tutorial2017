{
gROOT->Reset();
TFile *f = TFile::Open("Pixel.root");
TCanvas * Pixel = new TCanvas("Pixel", "Energy Deposit  & X vs Y");
Pixel->Divide(4);

Pixel->cd(1);
TH2D* wxy = (TH2D*)f->Get("h2:0");
wxy->Draw("SURF2");

TH1D * x = (TH1D*)f->Get("h1:0");
TH1D * y = (TH1D*)f->Get("h1:1");
TH1D * sum = (TH1D*)f->Get("h1:2");
Pixel->cd(2);
x->Draw("HIST");
Pixel->cd(3);
y->Draw("HIST");
Pixel->cd(4);
sum->Draw("HIST");

}

