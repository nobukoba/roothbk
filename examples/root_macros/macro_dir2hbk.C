/*
  Execute this macro as follows.
  
  $ root macro_dir2hbk.C
  
*/
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)
#endif

void macro_dir2hbk(){
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  gROOT->cd();
  TH1* h1 = new TH1D("h1","test1;aa;bb", 100,-4.,4.); 
  TH1* h2 = new TH1D("h2","test2", 100,-4.,4.);
  TH1* h3 = new TH1D("h3","test3", 100,-4.,4.);
  TH2* h4 = new TH2D("h4","test4", 30,-3.,3., 30,-3.,3.); 
  
  TRandom r;
  float a,b;
  for (int i = 1 ; i<= 10000000; i++){
    r.Rannor(a,b);
    h1->Fill(a,1.);
    h2->Fill(b,1.);
    h3->Fill(a*a+b*b,1.);
    h4->Fill(a,b,1.);
    if((i % 1000000) == 0){
      std::cout << "macro_dir2root in loop index " << i << std::endl;
    }
  }
  dir2hbk("dir2hbk.hb");
  return;
}
