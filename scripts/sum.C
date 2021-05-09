#include "TMatrixD.h"
#include "TH1F.h"
#include "TFile.h"
#include "TH2F.h"

#include <iostream>

void sum(Int_t qx = 0){
  TMatrixD mat(4096,4096);
  TH1F *h_e = new TH1F("h_e","h_e",4096,0,4096);
  int count = 0;
  for (Int_t i=0+qx*10;i!=99 + qx*10;i++){
    std::cout << i << std::endl;
    for (Int_t j=0;j!=10;j++){
      TFile file(Form("%d_%d.root",i,j));
      TH2F *hu1 = (TH2F*)file.Get("hu1");
      TH2F *hu1_m = (TH2F*)file.Get("hu1_m");

      for (Int_t k=0;k!=33;k++){
	for (Int_t p = 0; p !=4096; p++){
	  h_e->SetBinContent(p+1,h_e->GetBinContent(p+1) + hu1_m->GetBinContent(k+1,p+1));
	  for (Int_t q = 0; q!=4096; q++){
	    mat(p,q) += hu1->GetBinContent(k+1,p+1) * hu1->GetBinContent(k+1,q+1);
	  }
	}
	count ++;
      }

      delete hu1;
      delete hu1_m;
    }
  }

  mat *= 1./count;
  h_e->Scale(1./count);
  
  for (Int_t i=0;i!=4096;i++){
    h_e->SetBinContent(i+1,sqrt(h_e->GetBinContent(i+1)));
  }

  TFile *file1 = new TFile(Form("sum_%d.root",qx),"RECREATE");
  mat.Write("mat");
  h_e->SetDirectory(file1);
  file1->Write();
  file1->Close();
  

  // TMatrixD mat_u1(4096,4096);
  // TMatrixD mat_u2(4096,4096);
  // TMatrixD mat_v(4096,4096);
  // TMatrixD mat_w(4096,4096);

  // int count_u1 = 0;
  // int count_u2 = 0;
  // int count_v = 0;
  // int count_w = 0;
  
  // for (Int_t i=0;i!=100;i++){
  //   std::cout << i << std::endl;
  //   TFile file(Form("%d.root",i));
  //   TMatrixD *tmat_u1 = (TMatrixD*)file.Get("mat_u1");
  //   TMatrixD *tmat_u2 = (TMatrixD*)file.Get("mat_u2");
  //   TMatrixD *tmat_v = (TMatrixD*)file.Get("mat_v");
  //   TMatrixD *tmat_w = (TMatrixD*)file.Get("mat_w");

  //   TTree *T = (TTree*)file.Get("T");
  //   int n_u1, n_u2, n_v, n_w;
  //   T->SetBranchAddress("count_u1",&n_u1);
  //   T->SetBranchAddress("count_u2",&n_u2);
  //   T->SetBranchAddress("count_v",&n_v);
  //   T->SetBranchAddress("count_w",&n_w);
  //   T->GetEntry(0);

  //   count_u1 += n_u1;
  //   count_u2 += n_u2;
  //   count_v += n_v;
  //   count_w += n_w;

  //   mat_u1 += *tmat_u1;
  //   mat_u2 += *tmat_u2;
  //   mat_v += *tmat_v;
  //   mat_w += *tmat_w;


  //   delete tmat_u1;
  //   delete tmat_u2;
  //   delete tmat_v;
  //   delete tmat_w;
    
  //   file.Close();

   
  // }

  // mat_u1 *= 1./count_u1;
  // mat_u2 *= 1./count_u2;
  // mat_v *= 1./count_v;
  // mat_w *= 1./count_w;
  
  // for (Int_t q = 0; q!=4096;q++){
  //   for (Int_t p = q+1; p!=4096;p++){
  //     mat_u1(p,q) = mat_u1(q,p);
  //     mat_u2(p,q) = mat_u2(q,p);
  //     mat_v(p,q) = mat_v(q,p);
  //     mat_w(p,q) = mat_w(q,p);
  //   }
  // }
  
  // TFile *file1 = new TFile("sum.root","RECREATE");
  // mat_u1.Write("mat_u1");
  // mat_u2.Write("mat_u2");
  // mat_v.Write("mat_v");
  // mat_w.Write("mat_w");
  // file1->Write();
  // file1->Close();
  
}
