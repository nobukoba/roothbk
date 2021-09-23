#include <iostream>
#include "convertfunc.h"
#include "TSystem.h"

int main (int argc, char **argv) {
  /* For link option rpath. If the follwoing line is not written and
     LD_LIBRARY_PATH is set, another version of root lib may be loaded. */
  gSystem->Setenv("LD_LIBRARY_PATH","");
  if (argc < 2) {
    std::cout <<"Usage:   root2shm root_file_name shm_name" << std::endl;
    std::cout <<"Example: root2shm input.root TEST" << std::endl;
    std::cout <<"root_file_name:" << std::endl;
    std::cout <<"    Name of input ROOT file." << std::endl;
    std::cout <<"shm_name:" << std::endl;
    std::cout <<"    Name of the shared memory." << std::endl;
    std::cout <<"Note: This program does not support NTuples." << std::endl;
    return 0;
  }
  if(argc == 2){
    root2shm(argv[1],"");
  }else{
    root2shm(argv[1],argv[2]);
  }
  return 1;
}
