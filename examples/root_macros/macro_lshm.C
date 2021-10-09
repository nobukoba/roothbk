/*
  Execute this macro as follows.
  
  $ root macro_lshm.C
  
*/
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)
#endif

void macro_lshm(){
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  lshm();
  return;
}
