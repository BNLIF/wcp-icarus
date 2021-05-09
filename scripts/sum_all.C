void sum_all(){
  TMatrixD mat(4096,4096);
  TH1F *h_e = new TH1F("h_e","h_e",4096,0,4096);
  for (Int_t i=0;i!=10;i++){
    TFile file(Form("sum_%d.root",i));
    TMatrixD *temp_mat = (TMatrixD*)file.Get("mat");
    TH1F *temp_h_e = (TH1F*)file.Get("h_e");
    for (Int_t j=0;j!=4096;j++){
      h_e->SetBinContent(j+1,h_e->GetBinContent(j+1) + pow(temp_h_e->GetBinContent(j+1),2));
    }
    mat = mat + (*temp_mat);

    delete temp_mat;
    delete temp_h_e;
  }

  h_e->Scale(1./10.);
  mat *= 1./10.;
  
  for (Int_t j=0;j!=4096;j++){
    h_e->SetBinContent(j+1, sqrt(h_e->GetBinContent(j+1)));
  }
  

  TFile *file1 = new TFile("sum_all.root","RECREATE");
  mat.Write("mat");
  h_e->SetDirectory(file1);
  file1->Write();
  file1->Close();
}
