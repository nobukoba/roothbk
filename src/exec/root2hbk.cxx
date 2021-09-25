#include <iostream>
#include "convertfunc.h"
#include "TSystem.h"

int main (int argc, char **argv) {
  /* For link option rpath. If the follwoing line is not written and
     LD_LIBRARY_PATH is set, another version of root lib may be loaded. */
  gSystem->Setenv("LD_LIBRARY_PATH","");
  if (argc < 2) {
    std::cout <<"Usage:   root2hbk root_file_name hbk_file_name" << std::endl;
    std::cout <<"Example: root2hbk input.root output.hb" << std::endl;
    std::cout <<"root_file_name:" << std::endl;
    std::cout <<"    Name of an output ROOT file." << std::endl;
    std::cout <<"hbk_file_name:" << std::endl;
    std::cout <<"    Name of an input HBOOK file.  If this value is not given," << std::endl;
    std::cout <<"    The name is created from the input file name. For example," << std::endl;
    std::cout <<"    if the input file name is filename.root, the output is filename.hb" << std::endl;
    std::cout <<"Note: This program does not support NTuples." << std::endl;
    return 0;
  }
  if(argc == 2){
    root2hbk(argv[1],"");
  }else{
    root2hbk(argv[1],argv[2]);
  }
  return 1;
}
