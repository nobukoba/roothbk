/*
  First, execute the write_hbk.C macro to
  create the HBOOK file write_hbk.hb.
  Then, execute this macro as follows.
  
  $ root macro_hbk2srv.C
  
*/
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)  
#endif
 
void macro_hbk2srv(){
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  hbk2srv("write_hbk.hb");
  return;
}
