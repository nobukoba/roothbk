#include <stdio.h>
#include "cfortran.h"

int main (int argc, char **argv) {
  printf("pawc   %p\n",pawc_  );
  printf("quest  %p\n",quest_ );
  printf("hcbits %p\n",hcbits_);
  printf("hcbook %p\n",hcbook_);
  printf("rzcl   %p\n",rzcl_  );
  printf("zebq   %p\n",zebq_  );
  printf("mzcc   %p\n",mzcc_  );
  printf("pawc   d %d\n",(((unsigned long)pawc_  )&0xffffffff)/4);
  printf("quest  d %d\n",(((unsigned long)quest_ )&0xffffffff)/4);
  printf("hcbits d %d\n",(((unsigned long)hcbits_)&0xffffffff)/4);
  printf("hcbook d %d\n",(((unsigned long)hcbook_)&0xffffffff)/4);
  printf("rzcl   d %d\n",(((unsigned long)rzcl_  )&0xffffffff)/4);
  printf("zebq   d %d\n",(((unsigned long)zebq_  )&0xffffffff)/4);
  printf("mzcc   d %d\n",(((unsigned long)mzcc_  )&0xffffffff)/4);
  int pawc_size = PAWC_SIZE;
  printf("%d\n",pawc_size);
  hlimit_(pawc_size);
  printf("toy_c 1\n");
  hlimap_(0,"TE14",4);
  printf("toy_c 1\n");
  int idvec[1000000];
  int noh;
  hrin2_(0,9999,0);
  hidall_(idvec,noh);
  return 0;
}
