/*
  First, execute the write_shm.C macro to
  create histograms on shared memory named EXAM.
  Then, execute this macro as follows.
  
  $ root hbk2root.C
  
*/
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)  
#endif
 
void hbk2root(){
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  hbk2root();
  return;
}
