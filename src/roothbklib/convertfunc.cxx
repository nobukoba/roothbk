#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include "TROOT.h"
#include "TFile.h"
#include "TList.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include "TKey.h"
#include "TGraph.h"
#include "TSystem.h"
#include "TString.h"
#include "TXMLEngine.h"
#include "TBufferJSON.h"
#include "TMemFile.h"
#include "TSocket.h"
#include "TServerSocket.h"
#include "THttpServer.h"
#include "minicfortran.h"
#include "convertfunc.h"

int hbk_id_title_flag = 2;
int shms2srv_sync_flag = 1;

void hbk_id_title(int flag){
  hbk_id_title_flag = flag;
  return;
}

void shms2srv_sync(int flag){
  shms2srv_sync_flag = flag;
  return;
}

void dshm(const char* shm_name){
  std::string shm_name_str = shm_name;
  shm_name_str = shm_name_str.substr(0,4);
  unsigned int key = 0;
  for (int i = 0; i < 4; i++) {
    if (i < shm_name_str.length()) {
      key += ((int)shm_name[i])<<(i*8);
    }else{
      key += ((int)' ')<<(i*8);
    }
  }
  std::stringstream ss;
  ss << std::hex << key;
  std::string cmd;
  ss >> cmd;
  cmd = "ipcrm -M 0x" + cmd;
  std::cout << "Executing the system command: " << cmd << std::endl;
  system(cmd.c_str());
  return;
}

void lshm(){
  FILE* pipe = popen("ipcs -m", "r");
  char buffer[256];
  int nline = -1;
  while (fgets(buffer, 256, pipe) != NULL) {
    nline++;
    std::string buffer_str = buffer;
    if(buffer_str.length() < 2){
      continue;
    }
    if (buffer_str.back() == '\n'){
      buffer_str.pop_back();
    }
    while (buffer_str.back() == ' '){
      buffer_str.pop_back();
    }
    if (nline == 0) {
      std::cout << buffer_str << std::endl;
      continue;
    }else if(nline == 1) {
      std::cout << "-----" << buffer_str << std::endl;
      continue;
    }else if(nline == 2) {
      std::cout << "Name " << buffer_str << std::endl;
      continue;
    }
    std::stringstream ss;
    ss << std::hex << buffer_str.substr(0,10);
    unsigned int str_int = 0;
    ss >> str_int;
    std::string out_str = "";
    if ((str_int&0x000000ff)>0) {out_str += (char)((str_int&0x000000ff)>>0);}
    if ((str_int&0x0000ff00)>0) {out_str += (char)((str_int&0x0000ff00)>>8);}
    if ((str_int&0x00ff0000)>0) {out_str += (char)((str_int&0x00ff0000)>>16);}
    if ((str_int&0xff000000)>0) {out_str += (char)((str_int&0xff000000)>>24);}
    if (out_str.length()){
      std::cout << out_str << " " << buffer_str << std::endl;
    }else{
      std::cout << "     " << buffer_str << std::endl;
    }
  }
  pclose(pipe);
  return;
}

void init_hbook(){
  static int hlimit_flag = 0;
  if (hlimit_flag==0){
    int pawc_size = PAWC_SIZE;
    hlimit_(pawc_size);
    hlimit_flag = 1;
  }
  return;
}

std::string get_shm_names_str(const char *shm_names){
  std::string shm_names_str = shm_names;
  while (((int)shm_names_str.find(",")) > -1) {
    shm_names_str[shm_names_str.find(",")] = ' ';
  }
  for (int i = 0; i < shm_names_str.length(); i++) {
    if((int)(shm_names_str[i]) >= 0x61 &&
       (int)(shm_names_str[i]) <= 0x7a){
      shm_names_str[i] = (char)((int)shm_names_str[i] - 0x20);
    }
  }
  if (shm_names_str.length() == 0) {
    FILE* pipe = popen("ipcs -m", "r");
    char buffer[256];
    int nline = -1;
    while (fgets(buffer, 256, pipe) != NULL) {
      nline++;
      if (nline <= 2) {
	continue;
      }
      std::stringstream ss(buffer);
      std::string buffer_str;
      ss >> buffer_str;
      std::stringstream ss2;
      ss2 << std::hex << buffer_str;
      unsigned int str_int = 0;
      ss2 >> str_int;
      std::string out_str = "";
      if ((str_int&0x000000ff)>0) {out_str += (char)((str_int&0x000000ff)>>0);}
      if ((str_int&0x0000ff00)>0) {out_str += (char)((str_int&0x0000ff00)>>8);}
      if ((str_int&0x00ff0000)>0) {out_str += (char)((str_int&0x00ff0000)>>16);}
      if ((str_int&0xff000000)>0) {out_str += (char)((str_int&0xff000000)>>24);}
      if (out_str.length()){
	ss >> buffer_str;
	ss >> buffer_str;
	for (int i = 0; i < out_str.length(); i++) {
	  if((int)(out_str[i]) >= 0x61 &&
	     (int)(out_str[i]) <= 0x7a){
	    out_str[i] = (char)((int)out_str[i] - 0x20);
	  }
	}
	shm_names_str += out_str + "," + buffer_str + " ";
      }
    }
    pclose(pipe);
  }
  return shm_names_str;
}

void hrout_rec(const char *pawdir_in, const char *lundir_in) {
  /*std::cout <<  "pawdir_in: " << pawdir_in << std::endl;
    std::cout <<  "lundir_in: " << lundir_in << std::endl;*/
  std::string pawdir = pawdir_in;
  std::string lundir = lundir_in;
  hcdir_(pawdir.c_str(), " ", pawdir.length(), 1);
  hcdir_(lundir.c_str(), " ", lundir.length(), 1);
  int icycle = 0;
  hrout_(0,icycle," ",1);
  int ndir = 0;
  char subdirs[50][16];
  hrdir_(50, subdirs[0], ndir, 16);
  /*std::cout <<  "ndir: " << ndir << std::endl;*/
  char chdir[17];
  for (int k=0;k<ndir;k++) {
    strlcpy(chdir,subdirs[k],16);
    if (strchr(chdir,'/')) {
      printf("Sorry cannot convert directory name %s because it contains a slash\n",chdir);
      continue;
    }
    chdir[16] = 0;
    for (int i=16;i>0;i--) {
      if (chdir[i] == 0) continue;
      if (chdir[i] != ' ') break;
      chdir[i] = 0;
    }
    std::string new_pawdir = pawdir + "/" + chdir;
    std::string new_lundir = lundir + "/" + chdir;
    hrout_rec(new_pawdir.c_str(), new_lundir.c_str());
  }
  hcdir_(pawdir.c_str()," ",pawdir.length(),1);
  hcdir_(lundir.c_str()," ",lundir.length(),1);
  return;    
}

std::string open_input_shm(const char* shm_name){
  init_hbook();
  std::string shm_name_str = shm_name;
  shm_name_str = shm_name_str.substr(0,4);
  if (((int)shm_name_str.find(",")) > -1) {
    shm_name_str = shm_name_str.substr(0,shm_name_str.find(","));
  }
  for (int i = 0; i < shm_name_str.length(); i++) {
    if((int)(shm_name_str[i]) >= 0x61 &&
       (int)(shm_name_str[i]) <= 0x7a){
      shm_name_str[i] = (char)((int)shm_name_str[i] - 0x20);
    }
  }
  hlimap_(0,shm_name_str.c_str(),shm_name_str.length());
  hrin_(0,9999,0);
  hdelet_(0);
  if (quest_[0]) {
    printf("Error: cannot open the shared memory: %s\n",shm_name_str.c_str());
    return "";
  }
  shm_name_str = "//" + shm_name_str;
  return shm_name_str;
}

std::string open_input_hbk(const char* hbk_name){
  init_hbook();
  std::string hbk_name_str = hbk_name;
  int lun = 10, ier=0, record_size=0;
  hropen_(lun,"LUN10",hbk_name_str.c_str(),"x",record_size,ier,5,hbk_name_str.length(),1);
  if (ier)  {
    printf(" Error on hropen was %d \n", ier);
    return "";
  }
  if (quest_[0]) {
    printf("Error cannot open the HBOOK file: %s\n",hbk_name_str.c_str());
    return "";
  }
  hbk_name_str = "//LUN10";
  return hbk_name_str;
}

TFile* open_input_root(const char *root_name){
  std::string root_name_str = root_name;
  TFile *f = TFile::Open(root_name_str.c_str(),"read");
  if(!f) {
    std::cout << "Can not read the file: " << root_name_str << std::endl;
    return 0;
  }
  return f;
}

XMLDocPointer_t open_input_srv(TXMLEngine& xml, const char* srv_url){
  /* Now try to parse xml file
     Only file with restricted xml syntax are supported */
  TString srv_url_str = srv_url;
  TString cmd = "curl -s " + srv_url_str + "/h.xml";
  cmd.ReplaceAll(";","\\;");
  cmd.ReplaceAll("(","\\(");
  cmd.ReplaceAll(")","\\)");
  TString result = gSystem->GetFromPipe(cmd.Data());
  XMLDocPointer_t xmldoc = xml.ParseString(result);
  if (!xmldoc) {
    std::cout << "Error: XMLDocPointer_t xmldoc is null." << std::endl;
    return (XMLNodePointer_t) 0;
  }
  return xmldoc;
}

std::string open_output_shm(const char *name, const char* shm_name){
  init_hbook();
  std::string shm_name_str = shm_name;
  if (!shm_name_str.length()) {
    shm_name_str = name;
  }
  shm_name_str = shm_name_str.substr(0,4);
  /* Convert a-z to A-Z */
  for (int i = 0; i < shm_name_str.length(); i++) {
    if((int)(shm_name_str[i]) >= 0x61 &&
       (int)(shm_name_str[i]) <= 0x7a){
      shm_name_str[i] = (char)((int)shm_name_str[i] - 0x20);
    }
  }
  hlimap_(PAWC_SIZE,shm_name_str.c_str(),shm_name_str.length());
  return shm_name_str;
}

std::string open_output_hbk(const char* name, const char* hbk_name){
  init_hbook();
  std::string hbk_name_str = hbk_name;
  if(hbk_name_str.length()==0){
    hbk_name_str = name;
  }
  if (hbk_name_str.length()>=5 &&
      hbk_name_str.substr(hbk_name_str.length()-5) == ".root"){
    hbk_name_str = hbk_name_str.substr(0,hbk_name_str.length()-5);
  }
  hbk_name_str += ".hb";
  int lun = 10, ier=0, record_size=1024;
  hropen_(lun,"LUN10",hbk_name_str.c_str(),"n",record_size,ier,5,hbk_name_str.length(),1);
  if (ier)  {
    printf(" Error on hropen was %d\n", ier);
    return "";
  }
  if (quest_[0]) {
    printf("Error cannot open the HBOOK file: %s\n",hbk_name_str.c_str());
    return "";
  }
  hbk_name_str = "//LUN10";
  return hbk_name_str;
}

TFile* open_output_root(const char *name, const char *root_name){
  std::string root_name_str = root_name;
  if(root_name_str.length()==0){
    root_name_str = name;
  }
  if (root_name_str.length()>=3 &&
      root_name_str.substr(root_name_str.length()-3) == ".hb"){
    root_name_str = root_name_str.substr(0,root_name_str.length()-3);
  }
  if (root_name_str.length()>=4 &&
      root_name_str.substr(root_name_str.length()-4) == ".hbk"){
    root_name_str = root_name_str.substr(0,root_name_str.length()-4);
  }
  if (root_name_str.length()>=6 &&
      root_name_str.substr(root_name_str.length()-6) == ".hbook"){
    root_name_str = root_name_str.substr(0,root_name_str.length()-6);
  }
  if (root_name_str.length()>=5 &&
      root_name_str.substr(root_name_str.length()-5) == ".root"){
    root_name_str = root_name_str.substr(0,root_name_str.length()-5);
  }
  root_name_str += ".root";
  TFile * f = TFile::Open(root_name_str.c_str(),"recreate");
  if(!f) {
    std::cout << "Can not open the file: " << root_name_str << std::endl;
    return 0;
  }
  return f;
}

THttpServer* open_output_srv(int port) {
  static THttpServer* serv = 0;
  static int saved_port = 0;
  static int message_counter = 0;
  if(port < 0){
    if(serv != 0){
      std::cout << "THttpServer on port " << saved_port << " was deleted." << std::endl;
      delete serv;
      serv = 0;
    }
    return 0;
  }
  saved_port = port;
  if (serv == 0) {
    TServerSocket *ssocket = new TServerSocket(port);
    if(!ssocket->IsValid()){
      std::cout << "TServerSocket::GetErrorCode(): " << ssocket->GetErrorCode() << std::endl;
      std::cout << "Probably port: " << port << " is already in use." << std::endl;
      std::cout << "Exit."<< std::endl;
      delete ssocket;
      return 0;
    }else{
      std::cout << "The port is free." << std::endl;
      delete ssocket;
    }
    TString thttpserver_str = Form("http:%d?top=pid%d_at_%s", port, gSystem->GetPid(), gSystem->HostName());
    serv = new THttpServer(thttpserver_str.Data());
  }else{
    if (message_counter < 3) {
      std::cout << "THttpServer is already runing on port " << saved_port << "." << std::endl;
      std::cout << "Access to this THttpServer." << std::endl;
      message_counter++;      
    }
  }
  return serv;
}

void dir2hbk(TDirectory* root_dir, const char* hbk_name){
  if (root_dir == 0) {root_dir = gDirectory;}
  std::string hbk_name_str = open_output_hbk(root_dir->GetName(),hbk_name);
  if(hbk_name_str==""){return;}
  int shm_flag = 0;
  convert_dir_root2hbk(shm_flag,root_dir,"//PAWC","//LUN10");
  int icycle = 0;
  hrout_(0,icycle,"T",1);
  hrend_("LUN10",5);
  return;
}

void dir2root(TDirectory* root_dir, const char* root_name){
  if (root_dir == 0) {root_dir = gDirectory;}
  TFile *f = open_output_root(root_dir->GetName(),root_name);
  if (f==0) {return;}
  convert_dir_root2root(root_dir,(TDirectory*)f);
  f->Write();
  f->Close();
  return;
}

void dir2shm(TDirectory* root_dir, const char *shm_name){
  if (root_dir == 0) {root_dir = gDirectory;}
  std::string shm_name_str = open_output_shm(root_dir->GetName(),shm_name);
  if (shm_name_str =="") {return;}
  int shm_flag = 1;
  convert_dir_root2hbk(shm_flag,root_dir,"//PAWC","");
return;
}

void dir2srv(TDirectory* root_dir, int port) {
  THttpServer* serv = open_output_srv(port);
  if (serv == 0) {return;}
  if (gSystem->ProcessEvents()) {
    std::cout << "Error: gSystem->ProcessEvents() is null" << std::endl;
  }
  return;
}

void dir2hbk(const char* hbk_name){
  dir2hbk(0, hbk_name);
  return;
}
void dir2root(const char* root_name){
  dir2root(0, root_name);
  return;
}
void dir2shm(const char *shm_name){
  dir2shm(0, shm_name);
  return;
}
void dir2srv(int port){
  dir2srv(0, port);
  return;
}

void hbk2dir(const char *hbk_name, TDirectory* root_dir) {
  std::string hbk_name_str = open_input_hbk(hbk_name);
  if(hbk_name_str==""){return;}
  if (root_dir == 0) {root_dir = gROOT;}
  convert_dir_hbk2root(hbk_name_str.c_str(), root_dir);
  hrend_("LUN10",5);
  return;
}

void hbk2root(const char *hbk_name, const char *root_name) {
  std::string hbk_name_str = open_input_hbk(hbk_name);
  if(hbk_name_str==""){return;}
  TFile *f = open_output_root(hbk_name,root_name);
  if (f==0) {return;}
  convert_dir_hbk2root(hbk_name_str.c_str(), (TDirectory*)f);
  hrend_("LUN10",5);
  f->Write();
  f->Close();
  return;
}

void hbk2shm(const char* hbk_name, const char* shm_name){
  std::string shm_name_str = open_output_shm(hbk_name,shm_name);
  if (shm_name_str =="") {return;}
  std::string hbk_name_str = open_input_hbk(hbk_name);
  if(hbk_name_str==""){return;}
  int shm_flag = 0;
  convert_dir_hbk2hbk(shm_flag,hbk_name_str.c_str(),"//PAWC","");
  hcdir_("//PAWC"," ",6,1);
  hrend_("LUN10",5);
  return;
}

void hbk2srv(const char *hbk_name, int port, TDirectory* root_dir) {
  std::string hbk_name_str = open_input_hbk(hbk_name);
  if(hbk_name_str==""){return;}
  THttpServer* serv = open_output_srv(port);
  if (serv == 0) {return;}
  if (root_dir == 0) {root_dir = gROOT;}
  convert_dir_hbk2root(hbk_name_str.c_str(), root_dir);
  if (gSystem->ProcessEvents()) {
    std::cout << "Error: gSystem->ProcessEvents() is null" << std::endl;
  }
  return;
}

void root2dir(const char* root_name, TDirectory* root_dir){
  TFile *f = open_input_root(root_name);
  if (f==0) {return;}
  if (root_dir == 0) {root_dir = gROOT;}
  convert_dir_root2root((TDirectory*)f,root_dir);
  f->Write();
  f->Close();
  return;
}

void root2hbk(const char *root_name, const char* hbk_name){
  TFile *f = open_input_root(root_name);
  if (f==0) {return;}
  std::string hbk_name_str = open_output_hbk(root_name,hbk_name);
  if(hbk_name_str==""){return;}
  int shm_flag = 0;
  convert_dir_root2hbk(shm_flag,(TDirectory*)f,"//PAWC","//LUN10");
  int icycle = 0;
  hrout_(0,icycle,"T",1);
  hrend_("LUN10",5);
  f->Close();
  return;
}

void root2shm(const char *root_name, const char* shm_name){
  TFile *f = open_input_root(root_name);
  if (f==0) {return;}
  std::string shm_name_str = open_output_shm(root_name,shm_name);
  if (shm_name_str =="") {return;}
  int shm_flag = 1;
  convert_dir_root2hbk(shm_flag,(TDirectory*)f,"//PAWC","");
  f->Close();
  return;
}

void root2srv(const char *root_name, int port, TDirectory* root_dir) {
  TFile *f = open_input_root(root_name);
  if (f==0) {return;}
  THttpServer* serv = open_output_srv(port);
  if (serv == 0) {return;}
  if (root_dir == 0) {root_dir = gROOT;}
  convert_dir_root2root((TDirectory*)f, root_dir);
  if (gSystem->ProcessEvents()) {
    std::cout << "Error: gSystem->ProcessEvents() is null" << std::endl;
  }
  return;
}

void shm2dir(const char *shm_name, TDirectory* root_dir) {
  std::string shm_name_str = open_input_shm(shm_name);
  if(shm_name_str==""){return;}
  if (root_dir == 0) {root_dir = gROOT;}
  convert_dir_hbk2root(shm_name_str.c_str(), root_dir);
  shm_name_str = shm_name_str.substr(2,4);
  return;
}

void shm2hbk(const char* shm_name, const char* hbk_name){
  std::string shm_name_str = open_input_shm(shm_name);
  if(shm_name_str==""){return;}
  std::string hbk_name_str = open_output_hbk(shm_name,hbk_name);
  if(hbk_name_str==""){return;}
  int shm_flag = 1;
  hcdir_("//LUN10"," ",7,1);
  hcdir_("//PAWC"," ",6,1);
  convert_dir_hbk2hbk(shm_flag,shm_name_str.c_str(),"//PAWC","//LUN10");
  hcdir_("//PAWC"," ",6,1);
  hcdir_("//LUN10"," ",7,1);
  int icycle = 0;
  hrout_(0,icycle,"T",1);
  hrend_("LUN10",5);
  return;
}

void shm2root(const char *shm_name, const char *root_name) {
  std::string shm_name_str = open_input_shm(shm_name);
  if(shm_name_str==""){return;}
  TFile *f = open_output_root(shm_name,root_name);
  if (f==0) {return;}
  convert_dir_hbk2root(shm_name_str.c_str(), (TDirectory *)f);
  f->Write();
  f->Close();
  return;
}

void shm2srv(const char *shm_name, int port, TDirectory* root_dir) {
  std::string shm_name_str = open_input_shm(shm_name);
  if(shm_name_str==""){return;}
  THttpServer* serv = open_output_srv(port);
  if (serv == 0) {return;}
  if (root_dir == 0) {root_dir = gROOT;}
  convert_dir_hbk2root(shm_name_str.c_str(), root_dir);
  if (gSystem->ProcessEvents()) {
    std::cout << "Error: gSystem->ProcessEvents() is not null" << std::endl;
  }
  return;
}

void shms2dir(const char *shm_names, TDirectory* root_dir) {
  std::string shm_names_str = get_shm_names_str(shm_names);
  if (root_dir == 0) {root_dir = gROOT;}
  std::stringstream ss(shm_names_str);
  std::string shm_name_str;
  while(ss >> shm_name_str){
    if (((int)shm_name_str.find(",")) > -1) {
      shm_name_str[shm_name_str.find(",")] = '_';
    }
    TDirectory* cur_dir = (TDirectory*)root_dir->TDirectory::FindObject(shm_name_str.c_str());
    if (!cur_dir) {
      cur_dir = new TDirectoryFile(shm_name_str.c_str(), shm_name_str.c_str(), "", root_dir);
      if (!cur_dir) {
	printf("Error: can't open the direcotry: %s\n", shm_name_str.c_str());
	return;
      }
    }
    shm2dir(shm_name_str.c_str(), cur_dir);
  }
  return;
}

void shms2hbk(const char *shm_names, const char *hbk_name) {
  std::string shm_names_str = get_shm_names_str(shm_names);
  std::string hbk_name_str = open_output_hbk("shms",hbk_name);
  if(hbk_name_str==""){return;}
  std::stringstream ss(shm_names_str);
  std::string shm_name;
  while(ss >> shm_name){
    if (((int)shm_name.find(",")) > -1) {
      /*shm_name[shm_name.find(",")] = '_';*/
      shm_name = shm_name.substr(0,shm_name.find(","));
    }
    std::string shm_name_str = open_input_shm(shm_name.c_str());
    if(shm_name_str==""){return;}
    hcdir_("//LUN10"," ",7,1);
    hmdir_(shm_name.c_str(),"S",shm_name.length(),1);
    hcdir_("//PAWC"," ",6,1);
    hmdir_(shm_name.c_str(),"S",shm_name.length(),1);
    int shm_flag = 1;
    std::string new_paw_name_str = "//PAWC/" + shm_name;
    std::string new_hbk_name_str = "//LUN10/" + shm_name;
    convert_dir_hbk2hbk(shm_flag,shm_name_str.c_str(),
			new_paw_name_str.c_str(),new_hbk_name_str.c_str());
    hcdir_(shm_name_str.c_str()," ",shm_name_str.length(),1);
    hcdir_(new_paw_name_str.c_str()," ",new_paw_name_str.length(),1);
    hcdir_(new_hbk_name_str.c_str()," ",new_hbk_name_str.length(),1);
  }
  hcdir_("//PAWC"," ",6,1);
  hcdir_("//LUN10"," ",7,1);
  int icycle = 0;
  /*hrout_(0,icycle,"T",1);*/
  hrout_rec("//PAWC","//LUN10");
  hrend_("LUN10",5);
  return;
}

void shms2root(const char *shm_names, const char* root_name) {
  std::string shm_names_str = get_shm_names_str(shm_names);
  TFile *f = open_output_root("shms",root_name);
  if (f==0) {return;}
  std::stringstream ss(shm_names_str);
  std::string shm_name_str;
  while(ss >> shm_name_str){
    if (((int)shm_name_str.find(",")) > -1) {
      shm_name_str[shm_name_str.find(",")] = '_';
    }
    TDirectory* cur_dir = (TDirectory*)f->TDirectory::FindObject(shm_name_str.c_str());
    if (!cur_dir) {
      cur_dir = new TDirectoryFile(shm_name_str.c_str(), shm_name_str.c_str(), "", f);
      if (!cur_dir) {
	printf("Error: can't open the direcotry: %s\n", shm_name_str.c_str());
	return;
      }
    }
    shm2dir(shm_name_str.c_str(), cur_dir);
  }
  f->Write();
  f->Close();
  return;
}

void shms2srv(const char *shm_names, int port) {
  std::string shm_names_str = get_shm_names_str(shm_names);
  std::stringstream ss(shm_names_str);
  std::string shm_name_str;
  while(ss >> shm_name_str){
    if (((int)shm_name_str.find(",")) > -1) {
      shm_name_str[shm_name_str.find(",")] = '_';
    }
    TDirectory* f = (TDirectory*)gROOT->GetListOfFiles()->FindObject(shm_name_str.c_str());
    /*std::cout << "f: " <<  f << std::endl;*/
    if (!f) {
      f = new TMemFile(shm_name_str.c_str(), "recreate");
      /*std::cout << "f->GetName(): " <<  f->GetName() << std::endl;*/
      if (!f) {
	printf("Error: can't open the direcotry: %s\n", shm_name_str.c_str());
	return;
      }
    }
    shm2srv(shm_name_str.c_str(), port, f);
  }
  if(shms2srv_sync_flag == 1){
    int match_flag = 0;
    while (match_flag == 0){
      for (int i = 0; i < gROOT->GetListOfFiles()->GetEntries(); i++){
	TFile* f = (TFile*)gROOT->GetListOfFiles()->At(i);
	std::string classname = f->ClassName();
	match_flag = 0;
	if(classname == "TMemFile"){
	  std::stringstream ss2(shm_names_str);
	  std::string shm_name_str2;
	  while(ss2 >> shm_name_str2){
	    if (((int)shm_name_str2.find(",")) > -1) {
	      shm_name_str2[shm_name_str2.find(",")] = '_';
	    }
	    if (shm_name_str2 == f->GetName()) {
	      match_flag = 1;
	      break;
	    }
	  }
	  if (match_flag == 0){
	    delete f;
	    f = 0;
	    break;
	  }
	}
      }
    }
  }
  return;
}

void srv2dir(const char* srv_url, TDirectory* root_dir){
  TXMLEngine xml;
  XMLDocPointer_t xmldoc = open_input_srv(xml, srv_url);
  if(xmldoc == 0){return;}
  XMLNodePointer_t mainnode = xml.DocGetRootElement(xmldoc);
  XMLNodePointer_t child = xml.GetChild(mainnode);
  if (root_dir == 0) {root_dir = gROOT;}
  TString fulldir = "";
  convert_dir_srv2root(xml, child, 1, srv_url, fulldir, root_dir);
  xml.FreeDoc(xmldoc);
  return;
}

void srv2hbk(const char* srv_url, const char *hbk_name){
  TXMLEngine xml;
  XMLDocPointer_t xmldoc = open_input_srv(xml, srv_url);
  if(xmldoc == 0){return;}
  XMLNodePointer_t mainnode = xml.DocGetRootElement(xmldoc);
  XMLNodePointer_t child = xml.GetChild(mainnode);
  std::string hbk_name_str = open_output_hbk("http",hbk_name);
  if (hbk_name_str =="") {return;}
  TString fulldir = "";
  int shm_flag = 0;
  convert_dir_srv2hbk(shm_flag, xml, child, 1, srv_url, fulldir, "//PAWC","//LUN10");
  int icycle = 0;
  hrout_(0,icycle,"T",1);
  hrend_("LUN10",5);
  xml.FreeDoc(xmldoc);
  return;
}

void srv2root(const char* srv_url, const char* root_name){
  TXMLEngine xml;
  XMLDocPointer_t xmldoc = open_input_srv(xml, srv_url);
  if(xmldoc == 0){return;}
  XMLNodePointer_t mainnode = xml.DocGetRootElement(xmldoc);
  XMLNodePointer_t child = xml.GetChild(mainnode);
  TFile *f = open_output_root("thttpserver",root_name);
  if (f==0) {return;}
  TString fulldir = "";
  convert_dir_srv2root(xml, child, 1, srv_url, fulldir, (TDirectory*)f);
  xml.FreeDoc(xmldoc);
  f->Write();
  f->Close();
  return;
}

void srv2shm(const char* srv_url, const char *shm_name){
  TXMLEngine xml;
  XMLDocPointer_t xmldoc = open_input_srv(xml, srv_url);
  if(xmldoc == 0){return;}
  XMLNodePointer_t mainnode = xml.DocGetRootElement(xmldoc);
  XMLNodePointer_t child = xml.GetChild(mainnode);
  std::string shm_name_str = open_output_shm("http",shm_name);
  if (shm_name_str =="") {return;}
  TString fulldir = "";
  int shm_flag = 1;
  convert_dir_srv2hbk(shm_flag, xml, child, 1, srv_url, fulldir, "//PAWC","");
  xml.FreeDoc(xmldoc);
  return;
}

void convert_dir_hbk2hbk(int shm_flag, const char* cur_dir, const char *pawdir_in, const char *lundir_in) {
  std::string cur_dir_str = cur_dir;
  /*std::cout << "cur_dir_str:" << cur_dir_str << std::endl;*/
  hcdir_(cur_dir_str.c_str()," ",cur_dir_str.length(),1);
  hrin_(0,9999,0);
  /* converting subdirectories of this directory */
  int ndir = 0;
  char subdirs[50][16];
  hrdir_(50, subdirs[0], ndir, 16);
  /*std::cout <<  "ndir: " << ndir << std::endl;*/
  char chdir[17];
  for (int k=0;k<ndir;k++) {
    strlcpy(chdir,subdirs[k],16);
    /*std::cout <<  "subdirs[k]-->" <<  subdirs[0] << "<--" << std::endl;
      std::cout <<  "chdir-->" <<  chdir << "<--" << std::endl;*/
    if (strchr(chdir,'/')) {
      printf("Sorry cannot convert directory name %s because it contains a slash\n",chdir);
      continue;
    }
    /*std::cout << "chdir-->" << chdir << "<--" << std::endl;*/
    chdir[16] = 0;
    for (int i=16;i>0;i--) {
      if (chdir[i] == 0) continue;
      if (chdir[i] != ' ') break;
      chdir[i] = 0;
    }
    /*std::cout << "chdir-->" << chdir << "<--" << std::endl;*/
    std::string chdir_str = chdir; 
    std::string pawdir = pawdir_in;
    std::string lundir = lundir_in;
    if (shm_flag == 1) {
      hcdir_(lundir.c_str()," ",lundir.length(),1);
      hmdir_(chdir_str.c_str(),"S",chdir_str.length(),1);
    }
    hcdir_(pawdir.c_str()," ",pawdir.length(),1);
    hmdir_(chdir_str.c_str(),"S",chdir_str.length(),1);
    std::string new_pawdir = pawdir + "/" + chdir;
    std::string new_lundir = lundir + "/" + chdir;
    std::string new_cur_dir = cur_dir;
    new_cur_dir = new_cur_dir + "/" + chdir;
    convert_dir_hbk2hbk(shm_flag, new_cur_dir.c_str(), new_pawdir.c_str(), new_lundir.c_str());
    hcdir_(cur_dir_str.c_str()," ",cur_dir_str.length(),1);
    hcdir_(pawdir.c_str()," ",pawdir.length(),1);
    if (shm_flag == 1) {
      /*std::cout << "lundir: " << lundir << std::endl;*/
      hcdir_(lundir.c_str()," ",lundir.length(),1);
    }
  }
  return;
}

void convert_dir_root2root(TDirectory* cur_dir, TDirectory* output_dir){
  TList *list = cur_dir->GetListOfKeys();
  int key_flag = 0;
  if((list!=0) && (list->GetEntries()!=0)){
    key_flag = 1;
  }else{
    list = cur_dir->GetList();
    if(list==0) {
      return;
    }
  }
  for (int i = 0; i < list->GetEntries(); i++){
    TObject *obj;
    if (key_flag) {
      obj = ((TKey*)list->At(i))->ReadObj();
    }else{
      obj = list->At(i);
    }
    std::string classname = obj->ClassName();
    std::string objname = obj->GetName();
    /*std::cout << "objname: " << objname << std::endl;*/
    TClass *cl = gROOT->GetClass(classname.c_str());
    if (!cl) continue;
    if (cl->InheritsFrom(TDirectory::Class())) {
      /*std::cout << "Directory" << std::endl;
	std::cout << "objname: " << objname << std::endl;*/
      TDirectory* new_dir = (TDirectory*)output_dir->TDirectory::FindObject(objname.c_str());
      if (new_dir == 0) {
	new_dir = new TDirectoryFile(obj->GetName(),obj->GetTitle(),"",output_dir);
      }
      convert_dir_root2root((TDirectory*)obj, new_dir);
    } else if (cl->InheritsFrom(TTree::Class())) {
      continue;
    } else if (cl->InheritsFrom(TH1::Class())){
      /*std::cout << "TH1" << std::endl;*/
      TH1* hnew = (TH1*)output_dir->TDirectory::FindObject(objname.c_str());
      if (hnew != 0) {
	delete hnew;
	hnew = 0;
      }
      TDirectory* cursav = gDirectory;
      output_dir->cd();
      obj->Clone();
      cursav->cd();
    }
  }
  return;
}

void convert_dir_root2hbk(int shm_flag, TDirectory* cur_dir, const char *pawdir_in, const char *lundir_in) {
  /*std::cout << "convert_dir_root2hbook" << std::endl;*/
  TList *list = cur_dir->GetListOfKeys();
  int key_flag = 0;
  if((list!=0) && (list->GetEntries()!=0)){
    key_flag = 1;
  }else{
    list = cur_dir->GetList();
    if(list==0) {
      return;
    }
  }
  int id = 1;
  for (int i = 0; i < list->GetEntries(); i++){
    TObject *obj;
    if (key_flag) {
      obj = ((TKey*)list->At(i))->ReadObj();
    }else{
      obj = list->At(i);
    }
    std::string objname = obj->GetName();
    std::string classname = obj->ClassName();
    TClass *cl = gROOT->GetClass(classname.c_str());
    if (!cl) continue;
    if (cl->InheritsFrom(TDirectory::Class())) {
      /*std::cout << "Directory" << std::endl;
	std::cout << "objname: " << objname << std::endl;*/
      objname = objname.substr(0,16);
      /* Convert a-z to A-Z */
      for (int j = 0; j < objname.length(); j++) {
	if((int)(objname[j]) >= 0x61 &&
	   (int)(objname[j]) <= 0x7a){
	  objname[j] = (char)((int)objname[j] - 0x20);
	}
      }
      /*std::cout << "objname: " << objname << std::endl;*/
      while (((int)objname.find("/")) > -1) {
	objname[objname.find("/")] = '_';
      }
      while (((int)objname.find(".")) > -1) {
	objname[objname.find(".")] = '_';
      }
      std::string lundir = lundir_in;
      std::string pawdir = pawdir_in;
      if (shm_flag == 0) {
	hcdir_(lundir.c_str()," ",lundir.length(),1);
	hmdir_(objname.c_str(),"S",objname.length(),1);
      }
      hcdir_(pawdir.c_str()," ",pawdir.length(),1);
      hmdir_(objname.c_str(),"S",objname.length(),1);
      std::string new_pawdir = pawdir + "/" + objname;
      std::string new_lundir = lundir + "/" + objname;
      convert_dir_root2hbk(shm_flag,(TDirectory*)obj, new_pawdir.c_str(), new_lundir.c_str());
      hcdir_(pawdir.c_str()," ",pawdir.length(),1);
      if (shm_flag == 0) {
	hcdir_(lundir.c_str()," ",lundir.length(),1);
      }
    } else if (cl->InheritsFrom(TTree::Class())) {
      continue;
    } else if (cl->InheritsFrom(TH1::Class())){
      /*std::cout << "TH1" << std::endl;*/
      convert_histo_root2hbk((TH1*)obj, id);
      id = id + 1;
    }
  }
  return;
}

void convert_dir_hbk2root(const char *cur_dir, TDirectory* output_dir) {
  int idvec[100000];
  int imax = 0;
  std::string cur_dir_str = cur_dir;
  hcdir_(cur_dir_str.c_str()," ",cur_dir_str.length(),1);
  hrin_(0,9999,0);
  hidall_(idvec,imax);
  hdelet_(0);
  for (int i=0;i<imax;i++) {
    int id = idvec[i];
    int i999 = 999;
    hrin_(id,i999,0);
    if (quest_[0]) {
      printf("Error cannot read ID = %d\n",id);
      /* break; */
    }
    hdcofl_();
    /*lcid  = hcbook_[10];
      lcont = lq[lcid-1]; */
    if (hcbits_[3]) {
      /* skip ntuple Nobu 20210826
	 if (iq[lcid-2] == 2) convert_rwn(id);
	 else                 convert_cwn(id);*/
      hdelet_(id);
      continue;
    }
    if (hcbits_[0] && hcbits_[7]) {
      /* skip profile Nobu 20210826
	 convert_profile(id);*/
      hdelet_(id);
      continue;
    }
    if (hcbits_[0]) {
      convert_histo_hbk2root(id, 1, output_dir);
      hdelet_(id);
      continue;
    }
    if (hcbits_[1] || hcbits_[2]) {
      convert_histo_hbk2root(id, 2, output_dir);
      hdelet_(id);
    }
  }
  /* converting subdirectories of this directory */
  int ndir = 0;
  char subdirs[50][16];
  hrdir_(50, subdirs[0], ndir, 16);
  /*std::cout <<  "ndir: " << ndir << std::endl;*/
  char chdir[17];
  for (int k=0;k<ndir;k++) {
    strlcpy(chdir,subdirs[k],16);
    /*std::cout <<  "subdirs[k]-->" <<  subdirs[k] << "<--" << std::endl;
      std::cout <<  "chdir-->" <<  chdir << "<--" << std::endl;*/
    if (strchr(chdir,'/')) {
      printf("Sorry cannot convert directory name %s because it contains a slash\n",chdir);
      continue;
    }
    /*std::cout << "chdir: " << chdir << std::endl;*/
    chdir[16] = 0;
    for (int i=16;i>0;i--) {
      if (chdir[i] == 0) continue;
      if (chdir[i] != ' ') break;
      chdir[i] = 0;
    }
    /*std::cout << "chdir-->" << chdir << "<--" << std::endl;*/
    std::string chdir_str = chdir;
    TDirectory* new_dir = (TDirectory*)output_dir->TDirectory::FindObject(chdir_str.c_str());
    if (new_dir == 0) {
      new_dir = new TDirectoryFile(chdir_str.c_str(),chdir_str.c_str(),"",output_dir);
    }
    std::string new_cur_dir = cur_dir_str.c_str();
    new_cur_dir = new_cur_dir + "/" + chdir;
    convert_dir_hbk2root(new_cur_dir.c_str(),new_dir);
    hcdir_(cur_dir_str.c_str()," ",cur_dir_str.length(),1);
  }
  return;
}

void convert_dir_srv2hbk(int shm_flag, TXMLEngine &xml, XMLNodePointer_t node,
			 Int_t level, TString baseurl, TString fulldir,
			 const char *pawdir_in, const char *lundir_in){
  TString tmp_attr_kind = xml.GetAttr(node,"_kind");
  int open_itself_flag = 0;
  XMLNodePointer_t cur_node;
  if ((level == 1) &&
      (tmp_attr_kind.BeginsWith("ROOT.TH")||
       (!baseurl.EndsWith("/")))){
    cur_node = node;
    open_itself_flag = 1;
  }else{
    cur_node = xml.GetChild(node);
  }
  int id = 1;
  while (cur_node != 0) {
    TString attr_kind = xml.GetAttr(cur_node,"_kind");
    TString attr_name = xml.GetAttr(cur_node,"_name");
    TString attr_typename = xml.GetAttr(cur_node,"_typename");
    if(attr_typename.Length()>1){
    } else if (attr_kind.BeginsWith("ROOT.TH")) {
      TString cmd = "";
      if (open_itself_flag == 1) {
	cmd = "curl -s " + baseurl + "/root.json";
      }else{
	cmd = "curl -s " + baseurl + "/" + fulldir + "/" + attr_name + "/root.json";
      }
      cmd.ReplaceAll(";","\\;");
      cmd.ReplaceAll("(","\\(");
      cmd.ReplaceAll(")","\\)");
      std::cout << cmd << std::endl;
      TString result = gSystem->GetFromPipe(cmd.Data());
      TObject *obj = 0;
#if defined(NoFromJSON)
      std::cout << "No TBufferJSON::FromJSON" << std::endl;
      std::cout << "Use new ROOT version 6" << std::endl;
#else
      TBufferJSON::FromJSON(obj, result);
#endif
      if (obj) {
	convert_histo_root2hbk((TH1*)obj, id);
	id = id + 1;
	delete obj;
      }
    }else if(attr_kind.EqualTo("ROOT.Session")||
	     (attr_name.EqualTo("Files")&&attr_kind.EqualTo(""))||
	     attr_kind.EqualTo("ROOT.TMemFile")||
	     attr_kind.EqualTo("ROOT.TFile")||
	     attr_kind.BeginsWith("ROOT.TDirectory")){
      if(open_itself_flag == 0){
	fulldir += attr_name + "/";
      }
      if (attr_kind.EqualTo("ROOT.Session")||
	  (attr_name.EqualTo("Files")&&attr_kind.EqualTo(""))) {
        convert_dir_srv2hbk(shm_flag, xml, cur_node, level + 1,
			    baseurl, fulldir, pawdir_in, lundir_in);
      }else{
	std::string objname = attr_name.Data();
	objname = objname.substr(0,16);
	/* Convert a-z to A-Z */
	for (int j = 0; j < objname.length(); j++) {
	  if((int)(objname[j]) >= 0x61 &&
	     (int)(objname[j]) <= 0x7a){
	    objname[j] = (char)((int)objname[j] - 0x20);
	  }
	}
	/*std::cout << "objname: " << objname << std::endl;*/
	while (((int)objname.find("/")) > -1) {
	  objname[objname.find("/")] = '_';
	}
	while (((int)objname.find(".")) > -1) {
	  objname[objname.find(".")] = '_';
	}
	std::string lundir = lundir_in;
	std::string pawdir = pawdir_in;
	if (shm_flag == 0) {
	  hcdir_(lundir.c_str()," ",lundir.length(),1);
	  hmdir_(objname.c_str(),"S",objname.length(),1);
	}
	hcdir_(pawdir.c_str()," ",pawdir.length(),1);
	hmdir_(objname.c_str(),"S",objname.length(),1);
	std::string new_pawdir = pawdir + "/" + objname;
	std::string new_lundir = lundir + "/" + objname;
        convert_dir_srv2hbk(shm_flag, xml, cur_node, level + 1,
			    baseurl, fulldir,
			    new_pawdir.c_str(), new_lundir.c_str());
	hcdir_(pawdir.c_str()," ",pawdir.length(),1);
	if (shm_flag == 0) {
	  hcdir_(lundir.c_str()," ",lundir.length(),1);
	}
      }
    }
    if(open_itself_flag == 1){
      cur_node = 0;
    }else{
      cur_node = xml.GetNext(cur_node);
    }
  }
  return;
}

void convert_dir_srv2root(TXMLEngine &xml, XMLNodePointer_t node, Int_t level,
			  TString baseurl, TString fulldir, TDirectory* curdir){
  TString tmp_attr_kind = xml.GetAttr(node,"_kind");
  int open_itself_flag = 0;
  XMLNodePointer_t cur_node;
  if ((level == 1) &&
      (tmp_attr_kind.BeginsWith("ROOT.TH")||
       (!baseurl.EndsWith("/")))){
    cur_node = node;
    open_itself_flag = 1;
  }else{
    cur_node = xml.GetChild(node);
  }
  while (cur_node != 0) {
    TString attr_kind = xml.GetAttr(cur_node,"_kind");
    TString attr_name = xml.GetAttr(cur_node,"_name");
    TString attr_typename = xml.GetAttr(cur_node,"_typename");
    TDirectory* newdir = 0;
    if(attr_typename.Length()>1){
    }else if (attr_kind.BeginsWith("ROOT.TH")) {
      TString cmd = "";
      if (open_itself_flag == 1) {
	cmd = "curl -s " + baseurl + "/root.json";
      }else{
	cmd = "curl -s " + baseurl + "/" + fulldir + "/" + attr_name + "/root.json";
      }
      cmd.ReplaceAll(";","\\;");
      cmd.ReplaceAll("(","\\(");
      cmd.ReplaceAll(")","\\)");
      std::cout << cmd << std::endl;
      TString result = gSystem->GetFromPipe(cmd.Data());
      TObject *obj = 0;
#if defined(NoFromJSON)
      std::cout << "No TBufferJSON::FromJSON" << std::endl;
      std::cout << "Use new ROOT version 6" << std::endl;
#else
      TBufferJSON::FromJSON(obj, result);
#endif
      if (obj) {
	TH1* hnew = (TH1*)curdir->TDirectory::FindObject(obj->GetName());
	if (hnew != 0) {
	  delete hnew;
	  hnew = 0;
	}
	TDirectory* cursav = gDirectory;
	curdir->cd();
	obj->Clone();
	cursav->cd();
	delete obj;
      }
    }else if(attr_kind.EqualTo("ROOT.Session")||
	     (attr_name.EqualTo("Files")&&attr_kind.EqualTo(""))||
	     attr_kind.EqualTo("ROOT.TMemFile")||
	     attr_kind.EqualTo("ROOT.TFile")||
	     attr_kind.BeginsWith("ROOT.TDirectory")){
      if (attr_kind.EqualTo("ROOT.Session")||
	  (attr_name.EqualTo("Files")&&attr_kind.EqualTo(""))) {
	newdir = curdir;
      }else{
	newdir = (TDirectory*)curdir->TDirectory::FindObject(attr_name.Data());
	if (newdir == 0) {
	  newdir = new TDirectoryFile(attr_name.Data(),attr_name.Data(),"",curdir);
	}
      }
      if(open_itself_flag == 0){
	fulldir += attr_name + "/";
      }
      convert_dir_srv2root(xml, cur_node, level + 1, baseurl, fulldir, newdir);
    }
    if(open_itself_flag == 1){
      cur_node = 0;
    }else{
      cur_node = xml.GetNext(cur_node);
    }
  }
  return;
}

void convert_histo_root2hbk(TH1* h, int& id) {
  std::string classname = h->ClassName();
  TClass *cl = gROOT->GetClass(classname.c_str());
  int cur_kind = 0;
  if (cl->InheritsFrom(TH2::Class())){
    cur_kind = 2;
  } else if (cl->InheritsFrom(TH1::Class())){
    cur_kind = 1;
  }
  std::string idname = h->GetName();
  std::string idstr;
  int hbook_id = 0;
  if (idname.substr(0,2) == ("h_")) {
    idstr = idname.substr(2);
  }
  if (idname.substr(0,1) == "h") {
    idstr = idname.substr(1);
  }
  if(((int)idstr.find("_"))>-1){
    idstr = idstr.substr(0,idstr.find("_"));
  }
  std::stringstream ss(idstr);
  ss >> hbook_id;
  if (idname.substr(0,2) == ("h_")) {
    hbook_id = -hbook_id;
  }
  if (hbook_id == 0){
    hbook_id = id;
  }else if(hexist_(hbook_id)){
    while (hexist_(id)) {
      id++;
    }
    hcopy_(hbook_id, id, " ", 1);
    hdelet_(hbook_id);
  }
  std::string title  = h->GetTitle();
  std::string xtitle = h->GetXaxis()->GetTitle();
  std::string ytitle = h->GetYaxis()->GetTitle();
  if (xtitle != "") {
    title += ";" +  xtitle;
    if (ytitle != "") {
      title += ";" +  ytitle;
    }
  }else{
    if (ytitle != "") {
      title += ";;" +  ytitle;
    }
  }
  title = title.substr(0,80);
  if (cur_kind == 1) {
    int   ncx  = h->GetXaxis()->GetNbins();
    float vmx = 0.0;
    if (h->GetXaxis()->GetXbins()->GetSize()==0) {
      float xmin = h->GetXaxis()->GetXmin();
      float xmax = h->GetXaxis()->GetXmax();
      hbook1_(hbook_id, title.c_str(),ncx, xmin, xmax, vmx, title.length());
    }else{
      int nbinsp = h->GetXaxis()->GetXbins()->GetSize();
      float * xbins = new float[nbinsp];
      for (int i = 0; i < nbinsp; i++) {
	xbins[i] = h->GetXaxis()->GetXbins()->At(i);
      }
      hbookb_(hbook_id, title.c_str(),ncx, xbins, vmx, title.length());
      delete [] xbins;
    }
    float * ycon = new float[ncx];
    float * yerr = new float[ncx];
    for (int i = 1; i <= ncx; i++) {
      ycon[i-1] = h->GetBinContent(i);
      yerr[i-1] = h->GetBinError(i);
    }
    hpak_(hbook_id, ycon);
    hpake_(hbook_id, yerr);
    hf1_(hbook_id,h->GetBinCenter(0),h->GetBinContent(0));
    hf1_(hbook_id,h->GetBinCenter(ncx+1),h->GetBinContent(ncx+1));
    delete [] ycon;
    delete [] yerr;
  }else if (cur_kind == 2) {
    int   ncx  = h->GetXaxis()->GetNbins();
    float xmin = h->GetXaxis()->GetXmin();
    float xmax = h->GetXaxis()->GetXmax();
    int   ncy  = h->GetYaxis()->GetNbins();
    float ymin = h->GetYaxis()->GetXmin();
    float ymax = h->GetYaxis()->GetXmax();
    float vmx = 0.0;
    hbook2_(hbook_id, title.c_str(), ncx, xmin, xmax,
	    ncy, ymin, ymax, vmx, title.length());
    float *zcon = new float[ncx*ncy];
    float *zerr = new float[ncx*ncy];
    for (int i = 1; i <= ncx; i++) {
      for (int j = 1; j <= ncy; j++) {
	zcon[(i-1)+(j-1)*ncx] = h->GetBinContent(i,j);
	zerr[(i-1)+(j-1)*ncx] = h->GetBinError(i,j);
      }
    }
    hpak_(hbook_id, zcon);
    hpake_(hbook_id, zerr);
    for (int i = 0; i <= ncx+1; i++) {
      hf2_(hbook_id,
	   h->GetXaxis()->GetBinCenter(i),
	   h->GetYaxis()->GetBinCenter(0),
	   h->GetBinContent(i,0));
      hf2_(hbook_id,
	   h->GetXaxis()->GetBinCenter(i),
	   h->GetYaxis()->GetBinCenter(ncy+1),
	   h->GetBinContent(i,ncy+1));
    }
    for (int j = 1; j <= ncy; j++) {
      hf2_(hbook_id,
	   h->GetXaxis()->GetBinCenter(0),
	   h->GetYaxis()->GetBinCenter(j),
	   h->GetBinContent(0,j));
      hf2_(hbook_id,
	   h->GetXaxis()->GetBinCenter(ncx+1),
	   h->GetYaxis()->GetBinCenter(j),
	   h->GetBinContent(ncx+1,j));
    }
    delete [] zcon;
    delete [] zerr;
  }
  int nentires = h->GetEntries();
  /* Nobu's subroutine made from the hnoent subroutine */
  hnoentput_(hbook_id, nentires);
  /* Error bars will not be shown by default */
  hsifla_(9,0);
  /*hidopt_(hbook_id,"NERR",4);
    hidopt_(hbook_id,"NPER",4);*/
  return;
}

void convert_histo_hbk2root(int id, int kind, TDirectory* cur_dir) {
  char idname[128];
  if (id > 0) snprintf(idname,128,"h%d",id);
  else        snprintf(idname,128,"h_%d",-id);
  int nentries;
  hnoent_(id,nentries);
  char chtitl[128];
  int ncx,ncy,nwt,idb;
  float xmin,xmax,ymin,ymax;
  hgive_(id,chtitl,ncx,xmin,xmax,ncy,ymin,ymax,nwt,idb,80);
  chtitl[4*nwt] = 0;
  std::string chtitl_str = chtitl;
  while (chtitl_str.back() == ' '){
    chtitl_str.pop_back();
  }
  std::string xtitle = "";
  std::string ytitle = "";
  int dlmpos = chtitl_str.find(";");
  if (dlmpos > -1) {
    xtitle = chtitl_str.substr(dlmpos+1);
    chtitl_str = chtitl_str.substr(0,dlmpos);
  }
  dlmpos = xtitle.find(";");
  if (dlmpos > -1) {
    ytitle = xtitle.substr(dlmpos+1);
    xtitle = xtitle.substr(0,dlmpos);
  }
  /*std::string idname_title = Form("%s_%s",idname,chtitl_str.c_str());*/
  std::string idname_title = idname;
  if(hbk_id_title_flag > 0){
    idname_title += "_" + chtitl_str;
    if (hbk_id_title_flag == 2){
      std::stringstream ss("/ , . { } ( ) [ ] ? % # ! & ' - = ~ ^ |");
      std::string tmp_str = "";
      while (ss >> tmp_str){
	while (((int)idname_title.find(tmp_str.c_str())) > -1) {
	  idname_title[idname_title.find(tmp_str.c_str())] = '_';
	}
      }
      while (((int)idname_title.find(" ")) > -1) {
	idname_title[idname_title.find(" ")] = '_';
      }
    }
  }
  TH1* h = (TH1*)cur_dir->TDirectory::FindObject(idname_title.c_str());
  /*std::cout << "h: " << h << std::endl;*/
  int new_flag = 0;
  int cur_kind = 0;
  int *lq = &pawc_[9];
  int *iq = &pawc_[17];
  float *q = (float*)iq;
  if (h) {
    if(h->InheritsFrom("TH2")){
      cur_kind = 2;
    }else if (h->InheritsFrom("TH1")){
      cur_kind = 1;
    }
  }
  if(cur_kind != kind){
    new_flag = 1;
  }
  int lcid  = hcbook_[10];
  if(kind == 1){
    if(h){
      if(ncx != h->GetXaxis()->GetNbins()){
	new_flag = 1;
      }
      if (hcbits_[5]) {
	int lbins = lq[lcid-2];
	for (int i=0;i<=ncx;i++) {
	  if(q[lbins+i+1] != h->GetXaxis()->GetXbins()->GetArray()[i]){
	    new_flag = 1;
	  }
	}
      }else{
	if((xmin != h->GetXaxis()->GetXmin())||
	   (xmax != h->GetXaxis()->GetXmax())){
	  new_flag = 1;
	}
      }
    }
    if (new_flag == 1){
      if(h){
	delete h;
	h = 0;
      }
      if (hcbits_[5]) {
	int lbins = lq[lcid-2];
	float *xbins = new float[ncx+1];
	for (int i=0;i<=ncx;i++) xbins[i] = q[lbins+i+1];
	TDirectory* cursav = gDirectory;
	cur_dir->cd();
	h = new TH1F(idname_title.c_str(),chtitl_str.c_str(),ncx,xbins);
	/*std::cout << "h->GetName(): " << h->GetName() << std::endl;*/
	cursav->cd();
	delete [] xbins;
      } else {
	TDirectory* cursav = gDirectory;
	cur_dir->cd();
	h = new TH1F(idname_title.c_str(),chtitl_str.c_str(),ncx,xmin,xmax);
	/*std::cout << "h->GetName(): " << h->GetName() << std::endl;*/
	cursav->cd();
      }
      h->GetXaxis()->CenterTitle();
      h->GetYaxis()->CenterTitle();
    }
    /*std::cout << "'" << idname_title.c_str() << "'" << std::endl;*/
    if (hcbits_[8]) h->Sumw2();
    TGraph *gr = 0;
    if (hcbits_[11]) {
      std::cout << "hcbits_[11]:" << hcbits_[11] << std::endl;

      TDirectory* cursav = gDirectory;
      cur_dir->cd();
      gr = new TGraph(ncx);
      cursav->cd();
      h->GetListOfFunctions()->Add(gr);
    }
    float x;
    for (int i=0;i<=ncx+1;i++) {
      x = h->GetBinCenter(i);
      h->SetBinContent(i,hi_(id,i));
      /* if (hcbits_[8])*/
      hsifla_(9,1);
      h->SetBinError(i,hie_(id,i));
      if (gr && i>0 && i<=ncx) gr->SetPoint(i,x,hif_(id,i));
    }
    int kMIN1 = 7;
    int kMAX1 = 8;
    float yymin, yymax;
    if (hcbits_[19]) {
      yymax = q[lcid+kMAX1];
      h->SetMaximum(yymax);
    }
    if (hcbits_[20]) {
      yymin = q[lcid+kMIN1];
      h->SetMinimum(yymin);
    }
    h->SetOption("hist,func");
  }else if (kind==2){
    if(h){
      if((ncx != h->GetXaxis()->GetNbins())||
	 (xmin != h->GetXaxis()->GetXmin())||
	 (xmax != h->GetXaxis()->GetXmax())||
	 (ncy != h->GetYaxis()->GetNbins())||
	 (ymin != h->GetYaxis()->GetXmin())||
	 (ymax != h->GetYaxis()->GetXmax())){
	new_flag = 1;
      }
    }
    if (new_flag == 1){
      if(h){
	delete h;
	h = 0;
      }
      TDirectory* cursav = gDirectory;
      cur_dir->cd();
      h = new TH2F(idname_title.c_str(),chtitl_str.c_str(),ncx,xmin,xmax,ncy,ymin,ymax);
      /*std::cout << "h->GetName(): " << h->GetName() << std::endl;*/
      cursav->cd();
      h->GetXaxis()->CenterTitle();
      h->GetYaxis()->CenterTitle();
    }
    int lcont = lq[lcid-1];
    int lw = lq[lcont];
    if (lw) h->Sumw2();
    for (int j=0;j<=ncy+1;j++) {
      for (int i=0;i<=ncx+1;i++) {
	h->SetBinContent(i,j,hij_(id,i,j));
	if (lw) {
	  float err2 = hije_(id,i,j);
	  h->SetBinError(i,j,err2);
	}
      }
    }
    h->SetOption("colz");
  }
  h->GetXaxis()->SetTitle(xtitle.c_str());
  h->GetYaxis()->SetTitle(ytitle.c_str());
  h->SetEntries(nentries);
}
