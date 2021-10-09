/*
  First, execute the write_shm.C macro to
  create histograms on shared memory named EXAM.
  Then, execute this macro as follows.

  $ root shm2hbk.C

*/
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)  
#endif
 
void shm2hbk(){
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  shm2hbk();
  TH1* h1_test1 = (TH1*)gROOT->TDirectory::FindObject("h1_test1");
  h1_test1->Draw();
  return;
}
