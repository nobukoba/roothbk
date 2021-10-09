/*
  First, execute the macro_dir2root.C macro to
  create the ROOT file dir2root.root.
  Then, execute this macro as follows.

  $ root macro_root2dir.C

*/
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)  
#endif
 
void macro_root2dir(){
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  root2dir("dir2root.root");
  return;
}
