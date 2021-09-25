#include <iostream>
#include <string>
#include "minicfortran.h"
#include "hbkwrapper.h"

void hlimap(const char *shm_name) {
  std::string shm_name_str = shm_name;
  int pawc_size = PAWC_SIZE;
  hlimap_(pawc_size,shm_name_str.c_str(),shm_name_str.length());
  return;
}
void hbook1(const int id, const char* chtitl,
	    const int ncx, const float xmin, const float xmax){
  std::string chtitl_str = chtitl;
  float vmx = 0.0;
  hbook1_(id,chtitl_str.c_str(),ncx,xmin,xmax,vmx,chtitl_str.length());
  return;
}
void hbook2(const int id, const char* chtitl,
	    const int ncx, const float xmin, const float xmax,
	    const int ncy, const float ymin, const float ymax){
  std::string chtitl_str = chtitl;
  float vmx = 0.0;
  hbook2_(id, chtitl_str.c_str(),
	  ncx,xmin,xmax,ncy,ymin,ymax,
	  vmx,chtitl_str.length());
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
