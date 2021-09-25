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
    std::cout <<"Usage:   root2srv root_file_name [port]" << std::endl;
    std::cout <<"Example: root2srv input.root 8080" << std::endl;
    std::cout <<"root_file_name:" << std::endl;
    std::cout <<"    Name of an input ROOT file name." << std::endl;
    std::cout <<"port:" << std::endl;
    std::cout <<"    TCP port number of the THTTPserver" << std::endl;
    std::cout <<"Note: This program does not support Ntuples." << std::endl;
    return 0;
  }
  int port = 8080;
  if(argc == 2){
    root2srv(argv[1]);
  }else{
    std::stringstream ss(argv[2]);
    if (!(ss >> port)) {
      std::cout << "The port number is not valid." << std::endl;
      return 0;
    }
    root2srv(argv[1],port);
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
