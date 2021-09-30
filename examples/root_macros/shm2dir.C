#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)  
#endif
 
void shm2dir(){
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  shm2dir("EXAM");
  gROOT->ls();
  TH1* h1_test1 = (TH1*)gROOT->TDirectory::FindObject("h1_test1");
  h1_test1->Draw();
  return;
}
