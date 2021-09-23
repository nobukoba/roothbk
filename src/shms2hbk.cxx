#include <iostream>
#include "convertfunc.h"

int main (int argc, char **argv) {
  if (argc < 2) {
    std::cout <<"Usage:   shms2hbk shm_name_list [hbk_file_name]" << std::endl;
    std::cout <<"Example: shms2hbk TEST,FRED out.hb" << std::endl;
    std::cout <<"shm_name_list:" << std::endl;
    std::cout <<"    Should be separated by commas with no space." << std::endl;
    std::cout <<"    If an empty string \"\" is given, all shared " << std::endl;
    std::cout <<"    memories will be read." << std::endl;
    std::cout <<"hbk_file_name:" << std::endl;
    std::cout <<"    default value = shms.hb" << std::endl;
    std::cout <<"Note: This program does not support NTuples." << std::endl;
    return 0;
  }
  if(argc > 2){
    shms2hbk(argv[1],argv[2]);
  }else{
    shms2hbk(argv[1],"");
  }
  return 1;
}
