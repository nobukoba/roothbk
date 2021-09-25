#include <iostream>
#include "convertfunc.h"

int main (int argc, char **argv) {
  if (argc < 3) {
    std::cout <<"Usage:   hbk2shm hbk_file_name shm_name" << std::endl;
    std::cout <<"Example: hbk2shm input.hb TEST" << std::endl;
    std::cout <<"hbk_file_name:" << std::endl;
    std::cout <<"    Name of input HBOOK file." << std::endl;
    std::cout <<"shm_name:" << std::endl;
    std::cout <<"    Name of output shared memory" << std::endl;
    std::cout <<"Note: This program does not support NTuples." << std::endl;
    return 0;
  }
  hbk2shm(argv[1],argv[2]);
  return 1;
}
