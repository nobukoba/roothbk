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
    std::cout <<"Usage:   srv2hbk srv_url hbk_file_name" << std::endl;
    std::cout <<"Example: srv2hbk \"http://localhost:8080/\" output.hb" << std::endl;
    std::cout <<"srv_url:" << std::endl;
    std::cout <<"    URL where running the THttpServer" << std::endl;
    std::cout <<"hbk_file_name:" << std::endl;
    std::cout <<"    Name of an output HBOOK file name." << std::endl;
    std::cout <<"    Default value = http.hb" << std::endl;
    std::cout <<"Note: This program does not support Ntuples." << std::endl;
    return 0;
  }
  if(argc == 2){
    srv2hbk(argv[1],"");
  }else{
    srv2hbk(argv[1],argv[2]);
  }
  return 1;
}
