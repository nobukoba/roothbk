#include <iostream>
#include "convertfunc.h"

int main (int argc, char **argv) {
  if (argc < 2) {
    std::cout <<"Usage:   dshm shm_name" << std::endl;
    std::cout <<"Example: dshm TEST" << std::endl;
    return 0;
  }
  dshm(argv[1]);
  return 1;
}
