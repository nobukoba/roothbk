#ifndef cfortran_h
#define cfortran_h

/* Define the names of the Fortran common blocks for the different OSs
   Note that with gcc3.4 or above the size of PAWC_SIZE must be the same 
   as in the Fortran definition in hbook.f and zebra
   Also, the arrays must be declared extern like on Windows */
#define PAWC_SIZE 32000000
extern "C" int pawc_[PAWC_SIZE];
extern "C" int quest_[100];
extern "C" int hcbits_[37];
extern "C" int hcbook_[51];
extern "C" int rzcl_[11];
extern "C" int zebq_[104];
extern "C" int mzcc_[411];
extern "C" int bidon_[10006];
extern "C" int mzcwk_[5120];
extern "C" int fzcx_[71];
extern "C" int fzci_[78];

extern "C" void  hlimit_(const int&);
extern "C" void  hropen_(const int&,const char*,const char*,const char*,const int&,const int&,const int,const int,const int);
extern "C" void  hrin_(const int&,const int&,const int&);
extern "C" void  hnoent_(const int&,const int&);
extern "C" void  hgive_(const int&,const char*,const int&,const float&,const float&,const int&,const float&,const float&,const int&,const int&,const int);
extern "C" void  hgiven_(const int&,const char*,const int&,const char*,const float&,const float&,const int,const int);
extern "C" void  hntvar2_(const int&,const int&,const char*,const char*,const char*,int&,int&,int&,int&,int&,const int,const int, const int);
extern "C" void  hbnam_(const int&,const char*,const int&,const char*,const int&,const int, const int);
extern "C" void  hprntu_(const int&);
extern "C" void  hgnpar_(const int&,const char *,const int);
extern "C" void  hgnf_(const int&,const int&,const float&,const int&);
extern "C" void  hgnt_(const int&,const int&,const int&);
extern "C" void  rzink_(const int&,const int&,const char *,const int);
extern "C" void  hmaxim_(const int&,const float&);
extern "C" void  hminim_(const int&,const float&);
extern "C" void  hdelet_(const int&);
extern "C" void  hix_(const int&,const int&,const float&);
extern "C" void  hijxy_(const int&,const int&,const int&,const float&,const float&);
extern "C" float hi_(const int&,const int&);
extern "C" float hie_(const int&,const int&);
extern "C" float hif_(const int&,const int&);
extern "C" float hij_(const int&,const int&,const int&);
extern "C" float hije_(const int&,const int&,const int&);
extern "C" void  hcdir_(const char*,const char* ,const int,const int);
extern "C" void  zitoh_(const int&,const int&,const int&);
extern "C" void  uhtoc_(const int&,const int&,const char*,int&,const int);
/* --> Nobu added */
extern "C" void  hlimap_(const int&,const char*, const int);
extern "C" void  hidall_(const int*, const int&);
extern "C" void  hrin_(const int&,const int&,const int&);
extern "C" void  hrend_(const char*,const int);
extern "C" void  hdcofl_();
extern "C" void  hbook1_(const int&,const char*,const int&,const float&,const float&,const float&,const int);
extern "C" void  hbook2_(const int&,const char*,const int&,const float&,const float&,const int&,const float&,const float&,const float&,const int);
extern "C" void  hbookb_(const int&,const char*,const int&,const float*,const float&,const int);
extern "C" void  hf1_(const int&,const float&,const float&);
extern "C" void  hf2_(const int&,const float&,const float&,const float&);
extern "C" void  hfill_(const int&,const float&,const float&,const float&);
extern "C" void  htitle_(const char*, const int);
extern "C" float rndm_(const int&);
extern "C" void  rannor_(const float&,const float&);
extern "C" float hrndm_(const int&);
extern "C" float hrndm1_(const int&);
extern "C" void  hrndm2_(const int&,const float&,const float&);
extern "C" void  hmdir_(const char*,const char*, const int, const int);
extern "C" void  hrout_(const int&, const int&, const char*, const int);
extern "C" void  hcopy_(const int&,const int&,const char*,const int);
extern "C" bool  hexist_(const int&);
extern "C" void  hnoentput_(const int&,const int&);
extern "C" void  hpak_(const int&,const float*);
extern "C" void  hpake_(const int&,const float*);
extern "C" void  hidopt_(const int&,const char*,const int);
extern "C" void  hsifla_(const int&,const int&);
extern "C" void  hrdir_(const int&, char*,const int&,const int);
extern "C" int   hfreem_(long*);
extern "C" void  printaddr_();
/* --> Nobu */
#endif
