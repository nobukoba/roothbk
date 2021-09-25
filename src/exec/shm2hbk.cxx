#include <iostream>
#include "convertfunc.h"

int main (int argc, char **argv) {
  if (argc < 2) {
    std::cout <<"Usage:   shm2hbk shm_name [hbk_file_name]" << std::endl;
    std::cout <<"Example: shm2hbk TEST out.hb" << std::endl;
    std::cout <<"shm_name:" << std::endl;
    std::cout <<"    Name of the shared memory" << std::endl;
    std::cout <<"hbk_file_name:" << std::endl;
    std::cout <<"    default value = shms.hb" << std::endl;
    std::cout <<"Note: This program does not support NTuples." << std::endl;
    return 0;
  }
  if(argc > 2){
    shm2hbk(argv[1],argv[2]);
  }else{
    shm2hbk(argv[1],"");
  }
  return 1;
}
