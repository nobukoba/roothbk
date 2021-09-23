#include <iostream>
#include <unistd.h>
#include <sstream>
#include "convertfunc.h"
#include "TSystem.h"

int main (int argc, char **argv) {
  /* For link option rpath. If the follwoing line is not written and
     LD_LIBRARY_PATH is set, another version of root lib may be loaded. */
  gSystem->Setenv("LD_LIBRARY_PATH","");
  if (argc < 2) {
    std::cout <<"Usage:   srv2shm srv_url shm_name" << std::endl;
    std::cout <<"Example: srv2shm \"http://localhost:8080/\" TEST" << std::endl;
    std::cout <<"srv_url:" << std::endl;
    std::cout <<"    URL where running the THttpServer" << std::endl;
    std::cout <<"shm_name:" << std::endl;
    std::cout <<"    Name of a shared memory." << std::endl;
    std::cout <<"    Default value = HTTP" << std::endl;
    std::cout <<"Note: This program does not support Ntuples." << std::endl;
    return 0;
  }
  if(argc == 2){
    srv2shm(argv[1],"");
  }else{
    srv2shm(argv[1],argv[2]);
  }
  return 1;
}
