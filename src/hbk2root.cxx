#include <iostream>
#include "convertfunc.h"
#include "TSystem.h"

int main (int argc, char **argv) {
  /* For link option rpath. If the follwoing line is not written and
     LD_LIBRARY_PATH is set, another version of root lib may be loaded. */
  gSystem->Setenv("LD_LIBRARY_PATH","");
  if (argc < 2) {
    std::cout <<"Usage:   hbk2root hbk_file_name [root_file_name]" << std::endl;
    std::cout <<"Example: hbk2root input.hb output.root" << std::endl;
    std::cout <<"hbk_file_name:" << std::endl;
    std::cout <<"    Name of an input HBOOK file" << std::endl;
    std::cout <<"root_file_name:" << std::endl;
    std::cout <<"    Name of an output ROOT file. If this value is not given," << std::endl;
    std::cout <<"    The name is created from the input file name. For example," << std::endl;
    std::cout <<"    if the input file name is filename.hb, the output is filename.root" << std::endl;
    std::cout <<"Note: This program does not support NTuples." << std::endl;
    return 0;
  }
  if(argc == 2){
    hbk2root(argv[1],"");
  }else{
    hbk2root(argv[1],argv[2]);
  }
  return 1;
}
