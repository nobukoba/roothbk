/*
  First, execute the macro_dir2srv.C macro to
  run the THttpServer on port 8080.
  Then, execute this macro as follows.

  $ root macro_srv2shm.C

*/
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)  
#endif
 
void macro_srv2shm(){
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  srv2shm("http://localhost:8080");
  return;
}
