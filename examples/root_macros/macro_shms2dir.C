/*
  First, execute the write_shm.C macro to
  create histograms on shared memory named EXAM.
  Then, execute this macro as follows.

  $ root macro_shms2dir.C

*/
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)  
#endif
 
void macro_shms2dir(){
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  shms2dir();
  gROOT->ls();
  std::string homedir = gSystem->GetHomeDirectory();
  std::string dirname = gSystem->BaseName(homedir.c_str());
  dirname = "EXAM_" + dirname;
  TDirectory* d = (TDirectory*)gROOT->TDirectory::FindObject(dirname.c_str());
  TH1* h1_test1 = (TH1*)d->TDirectory::FindObject("h1_test1");
  h1_test1->Draw();
  return;
}
