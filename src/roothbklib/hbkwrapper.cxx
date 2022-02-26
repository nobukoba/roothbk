#include <iostream>
#include <string>
#include "minicfortran.h"
#include "hbkwrapper.h"

void hlimit(const int pawc_size) {
  hlimit_(pawc_size);
  return;
}

void  hropen(const int lun, const char* chtop,
	     const char* chfile, const char* chopt,
	     const int& lrec, const int& istat){
  std::string chtop_str = chtop;
  std::string chfile_str = chfile;
  std::string chopt_str = chopt;
  hropen_(lun, chtop_str.c_str(),
	  chfile_str.c_str(), chopt_str.c_str(),
	  lrec, istat,
	  chtop_str.length(),
	  chfile_str.length(),
	  chopt_str.length());
  return;
}

void hrin(const int id, const int icycle, const int iofset){
  hrin_(id, icycle, iofset);
}

void hrend(const char* chtop){
  std::string chtop_str = chtop;
  hrend_(chtop_str.c_str(), chtop_str.length());
  return;
}

void hrout(const int id, const int& icycle, const char* chopt){
  std::string chopt_str = chopt;
  hrout_(id, icycle, chopt_str.c_str(), chopt_str.length());
  return;
}

void hgive(const int id, const char* chtitl,
	    const int& nx, const float& xmi, const float& xma,
	    const int& ny, const float& ymi, const float& yma,
	    const int& nwt, const int& loc){
  hgive_(id, chtitl, nx, xmi, xma, ny, ymi, yma, nwt, loc, 80);
  return;
}

void hdelet(const int id){
  hdelet_(id);
  return;
}

void hidall(const int* idvect, const int& n){
  hidall_(idvect, n);
  return;
}

void hdcofl(){
  hdcofl_();
  return;
}

void hlimap(const char *shm_name) {
  std::string shm_name_str = shm_name;
  int pawc_size = PAWC_SIZE;
  hlimap_(pawc_size,shm_name_str.c_str(),shm_name_str.length());
  return;
}

void hlimap(const int pawc_size, const char *shm_name) {
  std::string shm_name_str = shm_name;
  hlimap_(pawc_size,shm_name_str.c_str(),shm_name_str.length());
  return;
}

void hbook1(const int id, const char* chtitl,
	    const int ncx, const float xmin, const float xmax){
  hbook1(id,chtitl,ncx,xmin,xmax,0.0);
  return;
}

void hbook1(const int id, const char* chtitl,
	    const int ncx, const float xmin, const float xmax, const float vmx){
  std::string chtitl_str = chtitl;
  hbook1_(id,chtitl_str.c_str(),ncx,xmin,xmax,vmx,chtitl_str.length());
  return;
}

void hbook2(const int id, const char* chtitl,
	    const int ncx, const float xmin, const float xmax,
	    const int ncy, const float ymin, const float ymax, const float vmx){
  std::string chtitl_str = chtitl;
  hbook2_(id, chtitl_str.c_str(),
	  ncx,xmin,xmax,ncy,ymin,ymax,
	  vmx,chtitl_str.length());
  return;
}

void hbook2(const int id, const char* chtitl,
	    const int ncx, const float xmin, const float xmax,
	    const int ncy, const float ymin, const float ymax){
  hbook2(id, chtitl, ncx, xmin, xmax, ncy, ymin, ymax, 0.0);
  return;
}

void  hcopy(const int id1,const int id2, const char* chtitl){
  std::string chtitl_str = chtitl;
  hcopy_(id1, id2, chtitl_str.c_str(), chtitl_str.length());
  return;
}

void hf1(const int id,const float x,const float weight){
  hf1_(id, x, weight);
  return;
}
void hf2(const int id,const float x,const float y,const float weight){
  hf2_(id, x, y, weight);
  return;
}
void hfill(const int id,const float x,const float y,const float weight){
  hfill_(id, x, y, weight);
  return;
}
void htitle(const char *title) {
  std::string title_str = title;
  htitle_(title_str.c_str(),title_str.length());
  return;
}
void hmdir(const char *chdir,const char *chopt){
  std::string chdir_str = chdir;
  std::string chopt_str = chopt;
  hmdir_(chdir_str.c_str(),chopt_str.c_str(),chdir_str.length(),chopt_str.length());
  return;
}
void hcdir(const char *chdir,const char *chopt){
  std::string chdir_str = chdir;
  std::string chopt_str = chopt;
  hcdir_(chdir_str.c_str(),chopt_str.c_str(),chdir_str.length(),chopt_str.length());
  return;
}

void hrdir(const int maxdir, char** chdir, const int& ndir){
  hrdir_(maxdir, chdir[0], ndir, 16);
  return;  
}

void rannor(const float& a, const float& b) {
  rannor_(a,b);
  return;
}
