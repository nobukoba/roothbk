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
    std::cout <<"Usage:   srv2hbk srv_url root_file_name" << std::endl;
    std::cout <<"Example: srv2hbk \"http://localhost:8080/\" output.root" << std::endl;
    std::cout <<"srv_url:" << std::endl;
    std::cout <<"    URL where running the THttpServer" << std::endl;
    std::cout <<"root_file_name:" << std::endl;
    std::cout <<"    Name of an output ROOT file name." << std::endl;
    std::cout <<"    Default value = thttpserver.root" << std::endl;
    std::cout <<"Note: This program does not support Ntuples." << std::endl;
    return 0;
  }
  if(argc == 2){
    srv2root(argv[1],"");
  }else{
    srv2root(argv[1],argv[2]);
  }
  return 1;
}
