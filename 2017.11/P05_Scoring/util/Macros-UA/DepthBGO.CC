{
    gROOT->Reset();
    
TFile *_file0 = TFile::Open("P05.root");
TCanvas * BGO = new TCanvas("BGO", "Energy Deposit ");
BGO->Divide(4,5);
TH1D * BGO1 = (TH1D*)_file0->Get("BGO1");
BGO->cd(1);
BGO1->Draw("HIST");
TH1D * BGO2 = (TH1D*)_file0->Get("BGO2");
BGO->cd(2);
BGO2->Draw("HIST");

TH1D * BGO3 = (TH1D*)_file0->Get("BGO3");
BGO->cd(3);
BGO3->Draw("HIST");

TH1D * BGO4 = (TH1D*)_file0->Get("BGO4");
BGO->cd(4);
BGO4->Draw("HIST");

TH1D * BGO5 = (TH1D*)_file0->Get("BGO5");
TH1D * BGO6 = (TH1D*)_file0->Get("BGO6");
TH1D * BGO7 = (TH1D*)_file0->Get("BGO7");
TH1D * BGO8 = (TH1D*)_file0->Get("BGO8");
TH1D * BGO9 = (TH1D*)_file0->Get("BGO9");
TH1D * BGO10 = (TH1D*)_file0->Get("BGO10");
TH1D * BGO11 = (TH1D*)_file0->Get("BGO11");
TH1D * BGO12 = (TH1D*)_file0->Get("BGO12");
TH1D * BGO13 = (TH1D*)_file0->Get("BGO13");
TH1D * BGO14 = (TH1D*)_file0->Get("BGO14");
TH1D * BGO15 = (TH1D*)_file0->Get("BGO15");
TH1D * BGO16 = (TH1D*)_file0->Get("BGO16");
TH1D * BGO17 = (TH1D*)_file0->Get("BGO17");
TH1D * BGO18 = (TH1D*)_file0->Get("BGO18");
TH1D * BGO19 = (TH1D*)_file0->Get("BGO19");
TH1D * BGO20 = (TH1D*)_file0->Get("BGO20");




BGO->cd(5);
BGO5->Draw("HIST");
BGO->cd(6);
BGO6->Draw("HIST");
BGO->cd(7);
BGO7->Draw("HIST");
BGO->cd(8);
BGO8->Draw("HIST");
BGO->cd(9);
BGO9->Draw("HIST");
BGO->cd(10);
BGO10->Draw("HIST");
BGO->cd(11);
BGO11->Draw("HIST");
BGO->cd(12);
BGO12->Draw("HIST");
BGO->cd(13);
BGO13->Draw("HIST");
BGO->cd(14);
BGO14->Draw("HIST");
BGO->cd(15);
BGO15->Draw("HIST");
BGO->cd(16);
BGO16->Draw("HIST");
BGO->cd(17);
BGO17->Draw("HIST");
BGO->cd(18);
BGO18->Draw("HIST");
BGO->cd(19);
BGO19->Draw("HIST");
BGO->cd(20);
BGO20->Draw("HIST");

}

