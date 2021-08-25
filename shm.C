#include "rootminipacklib.h"

int *iq, *lq;
float *q;
char idname[128];
int nentries;
char chtitl[128];
int ncx,ncy,nwt,idb;
int lcont, lcid, lcdir;
float xmin,xmax,ymin,ymax;
const Int_t kMIN1 = 7;
const Int_t kMAX1 = 8;

void shm (){
  lq = &pawc[9];
  iq = &pawc[17];
  void *qq = iq;
  q = (float*)qq;
  int pawc_size = PAWC_SIZE;
  hlimit(pawc_size);

  TString shm_name = "TEST";
  hlimap(0,shm_name.Data(),shm_name.Length());
  hrin2(0,9999,0);
  hdelet(0);
  if (quest[0]) {
    printf("Warning: cannot open the shared memory: %s\n",shm_name.Data());
    return;
  }
  
  return;
}
