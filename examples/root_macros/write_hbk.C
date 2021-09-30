/*
  How to execute
  
  $ root write_hbk.C
  
  Then this macro creates a HBOOK file write_hbk.hb

*/
#include <iostream>
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)  
#endif

int write_hbk() {
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  printaddr();
  /* If you want to change the value 32000000 of "hlimit(32000000)",
     also the "HCV(32000000-11)" in inc/hbook/hcbook.inc 
     should be modified in calling from C/C++ programs. */
  printaddr();
  hlimit(32000000);
  int ier=0, record_size=1024;
  hropen(10,"LUN10","write_hbk.hb","n",record_size,ier);
  if (ier)  {
    std::cout << " Error on hropen was " << ier << std::endl;
    return 1;
  }
  hbook1(1,"test1;aa;bb",100,-4.,4.,0.);
  hcopy(1,2,"test2");
  hcopy(1,3,"test3");
  hbook2(4,"test4",30,-3.,3.,30,-3.,3.,0.);

  for (int i = 1 ; i<= 10000000; i++){
    float a,b;
    rannor(a,b);
    hf1(1,a,1.);
    hf1(2,b,1.);
    hf1(3,a*a+b*b,1.);
    hf2(4,a,b,1.);
    hf2(5,a+1.,b+1.,1.);
    if((i % 1000000) == 0){
      std::cout << "write_hbk_cxx in loop index " << i << std::endl;
    }
  }
  int icycle = 0;
  hrout(0,icycle," ");
  hrend("LUN10");
  return 1;
}
