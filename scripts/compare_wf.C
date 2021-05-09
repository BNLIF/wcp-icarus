void compare_wf(int ch = 900){
  // TFile *file = new TFile("2.root");
  
  // TH2F *hu_orig = (TH2F*)file->Get("hu_orig111");
  // TH2F *hu_nf = (TH2F*)file->Get("hu_0");

  // TFile *file1 = new TFile("./icarus/icarus-data-check-3702-wc-denoise-colth3.root");
  // TH2F *hu_ref = (TH2F*)file1->Get("hu_raw111");

  TFile *file = new TFile("4_test.root");
  
 
  TH2F *hu_nf = (TH2F*)file->Get("hu_2");
  TH2F *hu_orig = (TH2F*)file->Get("hu_orig110");
  
  TFile *file1 = new TFile("icarus-data-check-4575-3156-wc-denoise.root");
  TH2F *hu_ref = (TH2F*)file1->Get("hu_raw110");
  

  
  
  gStyle->SetOptStat(0);
  
  //make per channel compare

  TH1F *h_old = new TH1F("h_old","h_old",4096,0,4096);
  TH1F *h_new = new TH1F("h_new","h_new",4096,0,4096);
  TH1F *h_ref = new TH1F("h_ref","h_ref",4096,0,4096);
	
  //make +-32 block of channel compare around given channel
	
  TH2F *h_old_2D = new TH2F("h_old_2D","h_old_2D",65,ch-32,ch+32,4096,0,4096);
TH2F *h_new_2D = new TH2F("h_new_2D","h_new_2D",65,ch-32,ch+32,4096,0,4096);
TH2F *h_ref_2D = new TH2F("h_ref_2D","h_ref_2D",65,ch-32,ch+32,4096,0,4096);


h_old_2D->Reset();
h_new_2D->Reset();
h_ref_2D->Reset();

  for (Int_t i=0;i!=4096;i++){
        for(int j = ch-32;j<ch+32;++j){
                h_old_2D->SetBinContent(h_old_2D->FindBin(i+1,j+1),0);
                 h_new_2D->SetBinContent(h_new_2D->FindBin(i+1,j+1),0);
                  h_ref_2D->SetBinContent(h_ref_2D->FindBin(i+1,j+1),0);
        }
  }


  for (Int_t i=0;i!=4096;i++){
    h_old->SetBinContent(i+1,hu_orig->GetBinContent(ch+1,i+1));
    h_new->SetBinContent(i+1,hu_nf->GetBinContent(ch+1,i+1));
    h_ref->SetBinContent(i+1,hu_ref->GetBinContent(ch+1,i+1));
	for(int j = ch-32;j<ch+32;++j){
		h_old_2D->SetBinContent(h_old_2D->FindBin(j+1,i+1),hu_orig->GetBinContent(j+1,i+1));
		 h_new_2D->SetBinContent(h_new_2D->FindBin(j+1,i+1),hu_nf->GetBinContent(j+1,i+1));
		  h_ref_2D->SetBinContent(h_ref_2D->FindBin(j+1,i+1),hu_ref->GetBinContent(j+1,i+1));
	}

  }
  TCanvas *c1 = new TCanvas("c1","c1",1600,800);
  c1->Divide(2,2);
  c1->cd(1);
  hu_orig->SetTitle("The original WF (hu_orig110)");
  hu_orig->Draw("COLZ");

  c1->cd(2);
    TLegend *leg = new TLegend( 0.70, 0.75, 0.90, 0.90 ) ;
    leg->AddEntry( h_old, "h_orig" ) ;
    leg->AddEntry( h_new, "h_nf" ) ;
    leg->AddEntry( h_ref, "h_ref" ) ;
    //Float_t sizeleg = leg->GetTextSize()*1.2;
    //leg->SetTextSize( sizeleg ) ;
    leg->SetFillColor( kWhite ) ;
 
  h_old->Draw();
  h_old->SetLineColor(kGreen);
  h_old->SetTitle(Form("ch: %d",int(hu_orig->GetXaxis()->GetBinCenter(ch+1))));
  
  h_new->SetLineColor(kRed);
  
  h_new->Draw("same");
  h_ref->Draw("same");
  h_ref->SetLineColor(kBlack);


leg->Draw();
  c1->cd(3);
  hu_nf->SetTitle("WF drom New NF(hu_nf)");
  hu_nf->Draw("COLZ");

  c1->cd(4);
  hu_ref->SetTitle("The Raw WF (hu_raw)");
  hu_ref->Draw("COLZ");

  double sum_orig = 0;
  double sum_ref = 0;
  double sum_nf = 0;
  for (Int_t i=0;i!=4096;i++){
    sum_orig += pow(h_old->GetBinContent(i+1),2);
    sum_ref += pow(h_ref->GetBinContent(i+1),2);
    sum_nf += pow(h_new->GetBinContent(i+1),2);
  }
  // std::cout << sum_orig << " " << sum_ref << " " << sum_nf << std::endl;
  std::cout << sqrt(sum_ref/sum_orig) << " " << sqrt(sum_nf/sum_orig) << std::endl;
  

  // hu_orig->GetXaxis()->SetRangeUser(14176,14176+31);
  // hu_nf->GetXaxis()->SetRangeUser(14176,14176+31);
  // hu_ref->GetXaxis()->SetRangeUser(14176,14176+31);

  
  
  // hu_ref->GetYaxis()->SetRangeUser(800,1200);
  // hu_orig->GetYaxis()->SetRangeUser(800,1200);
  // hu_nf->GetYaxis()->SetRangeUser(800,1200);
  hu_orig->GetZaxis()->SetRangeUser(-20,20);
  hu_nf->GetZaxis()->SetRangeUser(-20,20);
  hu_ref->GetZaxis()->SetRangeUser(-20,20);

  hu_ref->GetYaxis()->SetRangeUser(1400,1800);
  hu_orig->GetYaxis()->SetRangeUser(1400,1800);
  hu_nf->GetYaxis()->SetRangeUser(1400,1800);
  // hu_nf->GetZaxis()->SetRangeUser(-16,16);
  // hu_ref->GetZaxis()->SetRangeUser(-16,16);

  hu_orig->GetXaxis()->SetRangeUser(896,896+31);
  hu_nf->GetXaxis()->SetRangeUser(896,896+31);
  hu_ref->GetXaxis()->SetRangeUser(896,896+31);
 
  h_old_2D->GetYaxis()->SetRangeUser(1400,1800);
  h_new_2D->GetYaxis()->SetRangeUser(1400,1800);
  h_ref_2D->GetYaxis()->SetRangeUser(1400,1800);

  h_old_2D->GetXaxis()->SetRangeUser(890,930);
  h_new_2D->GetXaxis()->SetRangeUser(890,930);
  h_ref_2D->GetXaxis()->SetRangeUser(890,930);

  TCanvas *c2 = new TCanvas("c2","c2",1600,800);
  c2->Divide(2,2);
  c2->cd(1);
  h_old_2D->Draw("SURF1 MIN0");
  c2->cd(2);
  h_new_2D->Draw("SURF1 MIN0");
  c2->cd(3);
  h_ref_2D->Draw("SURF1 MIN0");
}
