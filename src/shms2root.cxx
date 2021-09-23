#include <iostream>
#include "convertfunc.h"
#include "TSystem.h"

int main (int argc, char **argv) {
  /* For link option rpath. If the follwoing line is not written and
     LD_LIBRARY_PATH is set, another version of root lib may be loaded. */
  gSystem->Setenv("LD_LIBRARY_PATH","");
  if (argc < 2) {
    std::cout <<"Usage:   shms2root shm_name_list [root_file_name]" << std::endl;
    std::cout <<"Example: shms2root TEST,FRED out.root" << std::endl;
    std::cout <<"shm_name_list:" << std::endl;
    std::cout <<"    Should be separated by commas with no space." << std::endl;
    std::cout <<"    If an empty string \"\" is given, all shared " << std::endl;
    std::cout <<"    memories will be read." << std::endl;
    std::cout <<"root_file_name:" << std::endl;
    std::cout <<"    default value = shms.root" << std::endl;
    std::cout <<"Note: This program does not support NTuples." << std::endl;
    return 0;
  }
  if(argc > 2){
    shms2root(argv[1],argv[2]);
  }else{
    shms2root(argv[1],"");
  }
  return 1;
}
