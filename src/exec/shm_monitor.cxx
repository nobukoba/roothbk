#include <iostream>
#include <sstream>
#include "convertfunc.h"
#include "TSystem.h"

int main (int argc, char **argv) {
  /* For link option rpath. If the follwoing line is not written and
     LD_LIBRARY_PATH is set, another version of root lib may be loaded. */
  gSystem->Setenv("LD_LIBRARY_PATH","");
  if (argc < 2) {
    std::cout <<"Usage:   shm_monitor port [shm_name_list]" << std::endl;
    std::cout <<"Example: shm_monitor 8080 TEST,FRED" << std::endl;
    std::cout <<"shm_name_list:" << std::endl;
    std::cout <<"    Should be separated by commas with no space." << std::endl;
    std::cout <<"    If an empty string \"\" is given, all shared " << std::endl;
    std::cout <<"    memories will be read." << std::endl;
    std::cout <<"port:" << std::endl;
    std::cout <<"    TCP port number of the THttpServer" << std::endl;
    std::cout <<"Note: This program does not support Ntuples." << std::endl;
    return 0;
  }
  int port;
  std::stringstream ss(argv[1]);
  if (!(ss >> port)) {
    std::cout << "The port number is not valid." << std::endl;
    return 0;
  }
  std::cout << "Now you can have access to http://" << gSystem->HostName() << ":"
	    << port << "/" << std::endl;
  std::cout << "Type ctrl-c to stop the program." << std::endl;
  while (1) {
    if(argc == 2){
      shms2srv("",port);
    }else{
      shms2srv(argv[2],port);
    }
    if (gSystem->ProcessEvents()) {
      std::cout << "Error: gSystem->ProcessEvents() is not null." << std::endl;
      break;
    }
    gSystem->Sleep(300);
  }
  return 1;
}
