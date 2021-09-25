#include <iostream>
#include "convertfunc.h"

int main (int argc, char **argv) {
  if (argc < 2) {
    std::cout <<"Usage:   dshm shm_name1 [shm_name...]" << std::endl;
    std::cout <<"Example: dshm SHM1 SHM2" << std::endl;
    return 0;
  }
  for (int i = 1; i < argc; i++) {
    dshm(argv[i]);
  }
  
  return 1;
}
