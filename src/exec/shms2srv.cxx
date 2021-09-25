#include <iostream>
#include <sstream>
#include "convertfunc.h"
#include "TSystem.h"

int main (int argc, char **argv) {
  /* For link option rpath. If the follwoing line is not written and
     LD_LIBRARY_PATH is set, another version of root lib may be loaded. */
  gSystem->Setenv("LD_LIBRARY_PATH","");
  if (argc < 2) {
    std::cout <<"Usage:   shms2srv shm_name_list [port]" << std::endl;
    std::cout <<"Example: shms2srv TEST,FRED 8080" << std::endl;
    std::cout <<"shm_name_list:" << std::endl;
    std::cout <<"    Should be separated by commas with no space." << std::endl;
    std::cout <<"    If an empty string \"\" is given, all shared " << std::endl;
    std::cout <<"    memories will be read." << std::endl;
    std::cout <<"port:" << std::endl;
    std::cout <<"    TCP port number of the THTTPserver" << std::endl;
    std::cout <<"Note: This program does not support Ntuples." << std::endl;
    return 0;
  }
  int port = 8080;
  if(argc == 2){
    shms2srv(argv[1]);
  }else{
    std::stringstream ss(argv[2]);
    if (!(ss >> port)) {
      std::cout << "The port number is not valid." << std::endl;
      return 0;
    }
    shms2srv(argv[1],port);
  }
  std::cout << "Now you can have access to http://localhost:"
	    << port << "/" << std::endl;
  std::cout << "Type ctrl-c to stop the program." << std::endl;
  while (1) {
    if (gSystem->ProcessEvents()) {
      std::cout << "Error: gSystem->ProcessEvents() is not null." << std::endl;
      break;
    }
    gSystem->Sleep(300);
  }
  return 1;
}
