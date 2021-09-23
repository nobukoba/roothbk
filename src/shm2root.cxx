#include <iostream>
#include "convertfunc.h"
#include "TSystem.h"

int main (int argc, char **argv) {
  /* For link option rpath. If the follwoing line is not written and
     LD_LIBRARY_PATH is set, another version of root lib may be loaded. */
  gSystem->Setenv("LD_LIBRARY_PATH","");
  if (argc < 2) {
    std::cout <<"Usage:   shm2root shm_name [root_file_name]" << std::endl;
    std::cout <<"Example: shm2root TEST out.root" << std::endl;
    std::cout <<"shm_name:" << std::endl;
    std::cout <<"    Name of the shared memory" << std::endl;
    std::cout <<"root_file_name:" << std::endl;
    std::cout <<"    Name of output ROOT file. If this value is" << std::endl;
    std::cout <<"    not given, <shm_name>.root is created." << std::endl;
    std::cout <<"Note: This program does not support NTuples." << std::endl;
    return 0;
  }
  if(argc == 2){
    shm2root(argv[1],"");
  }else{
    shm2root(argv[1],argv[2]);
  }
  return 1;
}
