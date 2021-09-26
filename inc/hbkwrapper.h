#ifndef hbkwrapper_h
#define hbkwrapper_h

#define pawc   pawc_  
#define quest  quest_ 
#define hcbits hcbits_
#define hcbook hcbook_
#define rzcl   rzcl_  
#define zebq   zebq_  
#define mzcc   mzcc_  
#define bidon  bidon_
#define mzcwk  mzcwk_
#define fzcx   fzcx_
#define fzci   fzci_

void  hlimit(const int);
void  hlimap(const char *);
void  hlimap(const int, const char *);
void  hropen(const int,const char*,const char*,const char*,const int&,const int&);
void  hrin2(const int,const int,const int);
void  hrend(const char*);
void  hrout(const int, const int&, const char*);
void  hgive(const int,const char*,const int&,const float&,const float&,const int&,const float&,const float&,const int&,const int&);
void  hdelet(const int);
void  hidall(const int*, const int&);
void  hdcofl();
void  hbook1(const int, const char*,
	     const int, const float, const float);
void  hbook1(const int, const char*,
	     const int, const float, const float,
	     const float);
void  hbook2(const int, const char*,
	     const int, const float, const float,
	     const int, const float, const float);
void  hbook2(const int, const char*,
	     const int, const float, const float,
	     const int, const float, const float,
	     const float);
void  hcopy(const int, const int, const char*);
void  hf1(const int, const float, const float);
void  hf2(const int, const float, const float, const float);
void  hfill(const int, const float, const float, const float);
void  htitle(const char *);
void  hmdir(const char *, const char *);
void  hcdir(const char *, const char *);
void  hrdir(const int, char**, const int&);
void  rannor(const float&, const float&);
void  printaddr();
#endif
