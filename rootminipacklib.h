#ifndef rootminipacklib_h
#define rootminipacklib_h

/* Define the names of the Fortran common blocks for the different OSs
   Note that with gcc3.4 or above the size of PAWC_SIZE must be the same 
   as in the Fortran definition in hbook.f and zebra
   Also, the arrays must be declared extern like on Windows */
#define PAWC_SIZE 32000000
#define bigbuf bigbuf_
#define pawc pawc_
#define quest quest_
#define hcbits hcbits_
#define hcbook hcbook_
#define rzcl rzcl_
extern "C" char bigbuf_[PAWC_SIZE];
extern "C" int pawc_[PAWC_SIZE];
extern "C" int quest_[100];
extern "C" int hcbits_[37];
extern "C" int hcbook_[51];
extern "C" int rzcl_[11];

/*  Define the names of the Fortran subroutine and functions for the different OSs */
extern "C" void hlimit_(const int&);
extern "C" void hropen_(const int&,const char*,const char*,const char*,const int&,const int&,const int,const int,const int);
extern "C" void hrin_(const int&,const int&,const int&);
extern "C" void hnoent_(const int&,const int&);
extern "C" void hgive_(const int&,const char*,const int&,const float&,const float&,const int&,const float&,const float&,const int&,const int&,const int);
extern "C" void hgiven_(const int&,const char*,const int&,const char*,const float&,const float&,const int,const int);
extern "C" void hntvar2_(const int&,const int&,const char*,const char*,const char*,int&,int&,int&,int&,int&,const int,const int, const int);
extern "C" void hbnam_(const int&,const char*,const int&,const char*,const int&,const int, const int);
extern "C" void hprntu_(const int&);
extern "C" void hgnpar_(const int&,const char *,const int);
extern "C" void hgnf_(const int&,const int&,const float&,const int&);
extern "C" void hgnt_(const int&,const int&,const int&);
extern "C" void rzink_(const int&,const int&,const char *,const int);
extern "C" void hdcofl_();
extern "C" void hmaxim_(const int&,const float&);
extern "C" void hminim_(const int&,const float&);
extern "C" void hdelet_(const int&);
extern "C" void hix_(const int&,const int&,const float&);
extern "C" void hijxy_(const int&,const int&,const int&,const float&,const float&);
extern "C" float hi_(const int&,const int&);
extern "C" float hie_(const int&,const int&);
extern "C" float hif_(const int&,const int&);
extern "C" float hij_(const int&,const int&,const int&);
extern "C" float hije_(const int&,const int&,const int&);
extern "C" void hcdir_(const char*,const char* ,const int,const int);
extern "C" void zitoh_(const int&,const int&,const int&);
extern "C" void uhtoc_(const int&,const int&,const char*,int&,const int);
extern "C" void hlimap_(const int&,const char*, const int); /* Nobu added */
extern "C" void hidall_(const int*, const int&);            /* Nobu added */
extern "C" void hrin2_(const int&,const int&,const int&);   /* nobu added */
extern "C" void hrend_(const char*,const int);              /* nobu added */

void hlimit(const int&);
void hropen(const int&,const char*,const char*,const char*,const int&,const int&,const int,const int,const int);
void hrin(const int&,const int&,const int&);
void hnoent(const int&,const int&);
void hgive(const int&,const char*,const int&,const float&,const float&,const int&,const float&,const float&,const int&,const int&,const int);
void hgiven(const int&,const char*,const int&,const char*,const float&,const float&,const int,const int);
void hntvar2(const int&,const int&,const char*,const char*,const char*,int&,int&,int&,int&,int&,const int,const int, const int);
void hbnam(const int&,const char*,const int&,const char*,const int&,const int, const int);
void hprntu(const int&);
void hgnpar(const int&,const char *,const int);
void hgnf(const int&,const int&,const float&,const int&);
void hgnt(const int&,const int&,const int&);
void rzink(const int&,const int&,const char *,const int);
void hdcofl();
void hmaxim(const int&,const float&);
void hminim(const int&,const float&);
void hdelet(const int&);
void hix(const int&,const int&,const float&);
void hijxy(const int&,const int&,const int&,const float&,const float&);
float hi(const int&,const int&);
float hie(const int&,const int&);
float hif(const int&,const int&);
float hij(const int&,const int&,const int&);
float hije(const int&,const int&,const int&);
void hcdir(const char*,const char* ,const int,const int);
void zitoh(const int&,const int&,const int&);
void uhtoc(const int&,const int&,const char*,int&,const int);
void hlimap(const int&,const char*, const int); /* Nobu added */
void hidall(const int*, const int&);            /* Nobu added */
void hrin2(const int&,const int&,const int&);   /* nobu added */
void hrend(const char*,const int);              /* nobu added */
#endif
