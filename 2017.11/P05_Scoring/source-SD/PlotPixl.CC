{
gROOT->Reset();
TFile *f = TFile::Open("Pixel.root");
TH2D* wxy = (TH2D*)f->Get("1");
wxy->Draw("HIST");

wxy->Draw("BOX");
wxy->Draw("SURF");
wxy->Draw("SURF2");
}

