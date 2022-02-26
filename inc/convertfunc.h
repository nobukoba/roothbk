#ifndef convertfunc_h
#define convertfunc_h
#include "TH1.h"
#include "TDirectory.h"
#include "TFile.h"
#include "TXMLEngine.h"
#include "TString.h"
 
void hbk_id_title(int);
void shms2srv_sync(int);
void lshm();
void dshm(const char *);

void init_hbook(const int);
void hnoent_put(const int, const int);
void hrout_rec(const char *, const char *);
std::string get_shm_names_str(const char *);
std::string open_input_shm(const char*);
std::string open_input_hbk(const char*);
TFile*      open_input_root(const char *);
XMLDocPointer_t open_input_srv(TXMLEngine&, const char*);
std::string open_output_shm(const char *, const char*);
std::string open_output_hbk(const char*, const char*);
TFile*      open_output_root(const char *, const char *);
TFile*      open_output_srv(const char *, int);

void  dir2hbk  (TDirectory* root_dir,      const char* hbk_name="");
void  dir2root (TDirectory* root_dir,      const char* root_name="");
void  dir2shm  (TDirectory* root_dir,      const char* shm_name="");
void  dir2srv  (TDirectory* root_dir,      int port=8080);
void  dir2hbk  (const char* hbk_name="");
void  dir2root (const char* root_name="");
void  dir2shm  (const char* shm_name="");
void  dir2srv  (int port=8080);

void  hbk2dir  (const char* hbk_name,      TDirectory* root_dir=0);
void  hbk2root (const char* hbk_name,      const char* root_name="");
void  hbk2shm  (const char* hbk_name,      const char* shm_name);
void  hbk2srv  (const char* hbk_name,      int port=8080, TDirectory* root_dir=0);

void  root2dir (const char* root_name,     TDirectory* root_dir=0);
void  root2hbk (const char* root_name,     const char* hbk_name="");
void  root2shm (const char* root_name,     const char* shm_name);
void  root2srv (const char* root_name,     int port=8080, TDirectory* root_dir=0);

void  shm2dir  (const char* shm_name,      TDirectory* root_dir=0);
void  shm2hbk  (const char* shm_name,      const char* hbk_name="");
void  shm2root (const char* shm_name,      const char *root_name="");
void  shm2srv  (const char* shm_name,      int port=8080, TDirectory* root_dir=0);

void  shms2dir (const char* shm_names="",  TDirectory* root_dir=0);
void  shms2hbk (const char* shm_names="",  const char* hbk_name="");
void  shms2root(const char* shm_names="",  const char* root_name="");
void  shms2srv (const char* shm_names="",  int port=8080);

void  srv2dir  (const char* srv_url,       TDirectory* root_dir=0);
void  srv2hbk  (const char* srv_url,       const char* hbk_name="");
void  srv2root (const char* srv_url,       const char* root_name="");
void  srv2shm  (const char* srv_url,       const char* shm_name="");

void  convert_dir_hbk2root(const char *, TDirectory*);
void  convert_dir_root2root(TDirectory*,TDirectory*);
void  convert_dir_root2hbk(int, TDirectory*,const char *,const char *);
void  convert_dir_hbk2hbk(int, const char *,const char *,const char *);
void  convert_dir_srv2root(TXMLEngine &, XMLNodePointer_t, Int_t,
			   TString, TString, TDirectory*);
void  convert_dir_srv2hbk(int, TXMLEngine &, XMLNodePointer_t,
                          Int_t, TString, TString,
			  const char *, const char *);
void  convert_histo_root2hbk(TH1*, int&);
void  convert_histo_hbk2root(int, int, TDirectory*);
#endif
