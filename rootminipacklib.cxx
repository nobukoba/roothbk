#include <iostream>
#include <string>
#include <sstream>
#include "TROOT.h"
#include "TSystem.h"
#include "TFile.h"
#include "TMemFile.h"
#include "TList.h"
#include "TString.h"
#include "TObjString.h"
#include "TDirectory.h"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"
#include "rootminipacklib.h"

int *iq, *lq;
float *q;
int lcont, lcid;

void init_rootminipacklib(){
  lq = &pawc[9];
  iq = &pawc[17];
  void *qq = iq;
  q = (float*)qq;
  int pawc_size = PAWC_SIZE;
  hlimit(pawc_size);
}

void open_shm(const char *arg = "") {
   TString str_shm_names = arg;
   Int_t all_read_flag = 0;
   if (str_shm_names.Length() == 0) {
     all_read_flag = 1;
   }
   TList shm_name_list;
   if (all_read_flag == 0){
     while(1){
       Int_t pos = str_shm_names.First(',');
       if(pos < 0){break;}
       TString substr = str_shm_names(0,pos);
       shm_name_list.Add(new TObjString(substr.Data()));
       str_shm_names=str_shm_names(pos+1,str_shm_names.Length());
     }
     shm_name_list.Add(new TObjString(str_shm_names.Data()));
     TIter next(&shm_name_list);
     TObjString * ostr;
     std::cout << "List of shared memory names:" << std::endl;
     while ((ostr = (TObjString*)next())){
       std::cout << "  " <<  ostr->GetString().Data() << std::endl;
     }
     std::cout << std::endl;
   }else{
     shm_name_list.Delete();
     TString cmd = "ipcs -m | perl -alne 'if($.>3){@arr = @F[0] =~ /.{2}/g; foreach(@arr){$_ =~ s/00//;}printf(\"%s \",pack(\"H*\", @arr[4].@arr[3].@arr[2].@arr[1]));}'";
     TString cmd_out = gSystem->GetFromPipe(cmd.Data());
     std::stringstream ss(cmd_out.Data());
     std::string std_str;
     while (ss >> std_str){
       shm_name_list.Add(new TObjString(std_str.c_str()));
     }
   }
   TIter next2(&shm_name_list);
   TObjString * ostr2;
   while ((ostr2 = (TObjString*)next2())){
     TString shm_name = ostr2->GetString();
     open_single_shm(shm_name.Data());
   }
   return;
}

void open_single_shm(const char* shm_name_c_str = "TEST") {
  TString shm_name = shm_name_c_str;
  hlimap(0,shm_name.Data(),shm_name.Length());
  if (quest[0]) {
    printf("Warning: cannot open the shared memory: %s\n",shm_name.Data());
  }
  return;
}
void load_shm() {
  hrin2(0,9999,0);
  hdelet(0);
  /* TString filename = Form("TMemFile%s",shm_name.Data()); */
  TString filename = Form("TMemFile");
  TMemFile * tmp = (TMemFile *)gDirectory->FindObject(filename.Data());
  if (tmp) {
    gDirectory->Remove(tmp);
    delete tmp;
  }
  TDirectory *cursav = gDirectory;
  TMemFile * transient = new TMemFile(filename.Data(),"RECREATE",filename.Data());
  if (!transient) {
    printf("Error: can't open the TMemFile: %s \n",filename.Data());
    return;
  }
  TDirectory* global_dir = gROOT;
  convert_directory("//example", transient, global_dir);
  transient->ls();
  cursav->cd();
  delete transient;
  return;
}

void convert_directory(const char *dir, TDirectory* tmemfile_dir, TDirectory* global_dir) {
   Int_t idvec[1000000];
   Int_t noh;
   hrin2(0,9999,0);
   hidall(idvec,noh);
   hdelet(0);
   for (Int_t i=0;i<noh;i++) {
     Int_t id = idvec[i];
      int i999 = 999;
      hrin2(id,i999,0);
      if (quest[0]) {
         printf("Error cannot read ID = %d\n",id);
         /* break; */
      }
      hdcofl();
      lcid  = hcbook[10];
      lcont = lq[lcid-1];
      if (hcbits[3]) {
	/* skip ntuple Nobu 20210826
	  if (iq[lcid-2] == 2) convert_rwn(id);
	  else                 convert_cwn(id);*/
         hdelet(id);
         continue;
      }
      if (hcbits[0] && hcbits[7]) {
	/* skip profile Nobu 20210826
	  convert_profile(id);*/
         hdelet(id);
         continue;
      }
      if (hcbits[0]) {
         convert_1d(id, tmemfile_dir, global_dir);
         hdelet(id);
         continue;
      }
      if (hcbits[1] || hcbits[2]) {
	convert_2d(id, tmemfile_dir, global_dir);
         hdelet(id);
      }
   }

   /* converting subdirectories of this directory */
   const Int_t kKLS = 26;
   const Int_t kKNSD = 23;
   Int_t lcdir = rzcl[2];
   Int_t ls = iq[lcdir+kKLS];
   Int_t ndir = iq[lcdir+kKNSD];
   Int_t nch=16;
   Int_t ihdir[4];
   Int_t ncw = 4;
   TDirectory *cursav = gDirectory;
   char chdir[17];
   char hbookdir[17];
   for (Int_t k=0;k<ndir;k++) {
      lcdir = rzcl[2];
      zitoh(iq[lcdir+ls+7*k],ihdir[0],ncw);
      for (Int_t i=0;i<17;i++) chdir[i] = 0;
      uhtoc(ihdir[0],ncw,chdir,nch ,16);
      /* do not process directory names containing a slash */
      if (strchr(chdir,'/')) {
         printf("Sorry cannot convert directory name %s because it contains a slash\n",chdir);
         continue;
      }   
      strlcpy(hbookdir,chdir,17);
      for (Int_t i=16;i>0;i--) {
         if (chdir[i] == 0) continue;
         if (chdir[i] != ' ') break;
         chdir[i] = 0;
      }
      hcdir(hbookdir," ",16,1);
      tmemfile_dir->cd();
      TDirectory *new_tmemfile_dir = new TDirectoryFile(chdir,chdir,"",tmemfile_dir);
      global_dir->cd();
      TDirectory *new_global_dir = new TDirectoryFile(chdir,chdir,"",global_dir);
      convert_directory(chdir,new_tmemfile_dir,new_global_dir);
      hcdir("\\"," ",1,1);
      cursav->cd();
   }
}

void convert_1d(Int_t id, TDirectory* tmemfile_dir, TDirectory* global_dir) {
   /* convert 1d histogram */
   char idname[128];
   if (id > 0) snprintf(idname,128,"h%d",id);
   else        snprintf(idname,128,"h_%d",-id);
   int nentries;
   hnoent(id,nentries);
   char chtitl[128];
   int ncx,ncy,nwt,idb;
   float xmin,xmax,ymin,ymax;
   hgive(id,chtitl,ncx,xmin,xmax,ncy,ymin,ymax,nwt,idb,80);
   chtitl[4*nwt] = 0;
   TString chtitl_str = chtitl;
   while (chtitl_str.EndsWith(" ")){
     chtitl_str.Remove(TString::kTrailing, ' ');
   }
   TString xtitle = "";
   TString ytitle = "";
   Int_t dlmpos = chtitl_str.First(";");
   if (dlmpos > -1) {
     xtitle = chtitl_str(dlmpos+1,chtitl_str.Length()-1);
     chtitl_str = chtitl_str(0,dlmpos);
   }
   dlmpos = xtitle.First(";");
   if (dlmpos > -1) {
     ytitle = xtitle(dlmpos+1,xtitle.Length()-1);
     xtitle = xtitle(0,dlmpos);
   }
   TString idname_title = Form("%s_%s",idname,chtitl_str.Data());
   TDirectory *cursav = gDirectory;
   TH1F *h1;
   if (hcbits[5]) {
      Int_t lbins = lq[lcid-2];
      Double_t *xbins = new Double_t[ncx+1];
      for (Int_t i=0;i<=ncx;i++) xbins[i] = q[lbins+i+1];
      tmemfile_dir->cd();
      h1 = new TH1F(idname_title.Data(),chtitl_str.Data(),ncx,xbins);
      delete [] xbins;
   } else {
      tmemfile_dir->cd();
      h1 = new TH1F(idname_title.Data(),chtitl_str.Data(),ncx,xmin,xmax);
   }
   h1->GetXaxis()->CenterTitle();
   h1->GetYaxis()->CenterTitle();
   h1->GetXaxis()->SetTitle(xtitle.Data());
   h1->GetYaxis()->SetTitle(ytitle.Data());
   if (hcbits[8]) h1->Sumw2();
   TGraph *gr = 0;
   if (hcbits[11]) {
      gr = new TGraph(ncx);
      h1->GetListOfFunctions()->Add(gr);
   }

   /*Float_t x,yx;*/
   Float_t x;
   for (Int_t i=0;i<=ncx+1;i++) {
      x = h1->GetBinCenter(i);
      /*The error calculation is wrong in ROOT v6.
	2020/05/01 Nobu
	yx = hi(id,i);
	h1->Fill(x,yx); */
      h1->SetBinContent(i,hi(id,i));
      if (hcbits[8]) h1->SetBinError(i,hie(id,i));
      if (gr && i>0 && i<=ncx) gr->SetPoint(i,x,hif(id,i));
   }
   Int_t kMIN1 = 7;
   Int_t kMAX1 = 8;
   Float_t yymin, yymax;
   if (hcbits[19]) {
      yymax = q[lcid+kMAX1];
      h1->SetMaximum(yymax);
   }
   if (hcbits[20]) {
      yymin = q[lcid+kMIN1];
      h1->SetMinimum(yymin);
   }
   h1->SetEntries(nentries);
   global_dir->cd();
   h1->Clone();
   cursav->cd();
}

void convert_2d(Int_t id, TDirectory* tmemfile_dir, TDirectory* global_dir) {
   /* convert 2d histogram */
   char idname[128];
   if (id > 0) snprintf(idname,128,"h%d",id);
   else        snprintf(idname,128,"h_%d",-id);
   int nentries;
   hnoent(id,nentries);
   char chtitl[128];
   int ncx,ncy,nwt,idb;
   float xmin,xmax,ymin,ymax;
   hgive(id,chtitl,ncx,xmin,xmax,ncy,ymin,ymax,nwt,idb,80);
   chtitl[4*nwt] = 0;
   TString chtitl_str = chtitl;
   while (chtitl_str.EndsWith(" ")){
     chtitl_str.Remove(TString::kTrailing, ' ');
   }
   TString xtitle = "";
   TString ytitle = "";
   Int_t dlmpos = chtitl_str.First(";");
   if (dlmpos > -1) {
     xtitle = chtitl_str(dlmpos+1,chtitl_str.Length()-1);
     chtitl_str = chtitl_str(0,dlmpos);
   }
   dlmpos = xtitle.First(";");
   if (dlmpos > -1) {
     ytitle = xtitle(dlmpos+1,xtitle.Length()-1);
     xtitle = xtitle(0,dlmpos);
   }
   TString idname_title = Form("%s_%s",idname,chtitl_str.Data());
   TDirectory *cursav = gDirectory;
   tmemfile_dir->cd();
   TH2F *h2 = new TH2F(idname_title.Data(),chtitl,ncx,xmin,xmax,ncy,ymin,ymax);
   Float_t offsetx = 0.5*(xmax-xmin)/ncx;
   Float_t offsety = 0.5*(ymax-ymin)/ncy;
   Int_t lw = lq[lcont];
   if (lw) h2->Sumw2();

   Float_t x = 0.0, y = 0.0;
   for (Int_t j=0;j<=ncy+1;j++) {
      for (Int_t i=0;i<=ncx+1;i++) {
	/*The error calculation is wrong in ROOT v6.
	  2020/05/01 Nobu
         hijxy(id,i,j,x,y);
         h2->Fill(x+offsetx,y+offsety,hij(id,i,j));*/
         h2->SetBinContent(i,j,hij(id,i,j));
         if (lw) {
            Double_t err2 = hije(id,i,j);
            h2->SetCellError(i,j,err2);
         }
      }
   }
   h2->SetEntries(nentries);
   h2->SetOption("colz");
   global_dir->cd();
   h2->Clone();
   cursav->cd();
}
