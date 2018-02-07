#include <unistd.h>
#include "cd.h"
#include <cstdlib>
#include <iostream>
#include <string.h>
/*   This function implements cd command     
      RETURN VALUE: int status               
*/
int cd(char** argArray){
  if(argArray[1] == NULL){
    return 1;
  }
  else{
    if (chdir(argArray[1]) != 0) {
      std::cerr<<"cd failed"<<std::endl;
      }
  }
  return 1;
}
