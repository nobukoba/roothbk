/*
  First, execute the write_hbk.C macro to
  create the write_hbk.hb file. Then,
  Execute this macro as follows.

  $ root read_hbk.C

*/

#include <iostream>
#if defined(__CLING__)
R__LOAD_LIBRARY(../../lib/libroothbklib.so)  
#endif

int read_hbk() {
#if defined(__CINT__)
  gSystem->Load("../../lib/libroothbklib.so");
#endif
  /* If you want to change the value 32000000 of "hlimit(32000000)",
     also the "HCV(32000000-11)" in inc/hbook/hcbook.inc 
     should be modified in calling from C/C++ programs. */
  hlimit(32000000);
  int ier=0, record_size=0;
  hropen(10,"LUN10","write_hbk.hb","x",record_size,ier);
  if (ier)  {
    std::cout << " Error on hropen was " << ier << std::endl;
    return 1;
  }
  int idvec[10000];
  int imax = 0;
  hrin(0,9999,0);
  hidall(idvec,imax);
  hdelet(0);
  for (int i=0;i<imax;i++) {
    int id = idvec[i];
    hrin(id,999,0);
    if (quest[0]) {
      printf("Error cannot read ID = %d\n",id);
    }
    hdcofl();
    std::cout << "id: " << id <<std::endl;
    char chtitl[81];
    int ncx,ncy,nwt,idb;
    float xmin,xmax,ymin,ymax;
    if (hcbits[0]) {
      hgive(id,chtitl,ncx,xmin,xmax,ncy,ymin,ymax,nwt,idb);
      chtitl[4*nwt] = 0;
      std::string chtitl_str = chtitl;
      while (chtitl_str.back() == ' '){
	chtitl_str.pop_back();
      }
      std::cout << "type: 1d" <<std::endl;
      std::cout << "title: " << chtitl_str <<std::endl;
      std::cout << "xbins: " << ncx;
      std::cout << ", xmin: " << xmin;
      std::cout << ", xmax: " << xmax;
      std::cout << std::endl;
    }
    if (hcbits[1] || hcbits[2]) {
      hgive(id,chtitl,ncx,xmin,xmax,ncy,ymin,ymax,nwt,idb);
      chtitl[4*nwt] = 0;
      std::string chtitl_str = chtitl;
      while (chtitl_str.back() == ' '){
	chtitl_str.pop_back();
      }
      std::cout << "type: 2d" <<std::endl;
      std::cout << "title: " << chtitl_str <<std::endl;
      std::cout << "xbins: " << ncx;
      std::cout << ", xmin: " << xmin;
      std::cout << ", xmax: " << xmax << std::endl;
      std::cout << "ybins: " << ncy;
      std::cout << ", ymin: " << ymin;
      std::cout << ", ymax: " << ymax << std::endl;
    }
    std::cout << std::endl;
    hdelet(id);
  }
  hrend("LUN10");
  return 1;
}
