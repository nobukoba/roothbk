#ifndef roothbklib_h
#define roothbklib_h
/* Prototype declaration */
void  hlimap(const char *);
void  hbook1(const int, const char*,
	     const int, const float, const float);
void  hbook2(const int, const char*,
	     const int, const float, const float,
	     const int, const float, const float);
void  hf1(const int,const float,const float);
void  hf2(const int,const float,const float,const float);
void  hfill(const int,const float,const float,const float);
void  htitle(const char *);
float rndm(const int);
void  rannor(const float&,const float&);
float hrndm(const int);
float hrndm1(const int);
void  hrndm2(const int,const float&,const float&);
void  hmdir(const char *chdir,const char *chopt);
void  hcdir(const char *chdir,const char *chopt);
#endif
