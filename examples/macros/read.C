void read(){
  gROOT->ProcessLine(".L ../lib/libroothbklib.so");
  gROOT->ProcessLine("shm2dir(\"EXAM\")");
  gROOT->ProcessLine("h1_test1->Draw()");
  return;
}
