/*
  First, execute the write_shm.C macro to
  create histograms on shared memory named EXAM.
  Then, execute this macro as follows.

  $ root root2shm.C

*/
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)
#endif
 
void root2shm(){
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  root2shm();
  return;
}
