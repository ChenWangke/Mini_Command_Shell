#include "exportVar.h"
#include <cstdlib>
#include <iostream>

/* This function implements export command
   It searches var in mymap, find its paired value, 
   then use setenv(var,value,1) to put var=value in environ    
   RETURN VALUE: int status                                
*/
int exportVar(char** argArray, std::map<std::string,std::string> &mymap) {
  int i = 0;
  while(argArray[i] != NULL) {
    i++;
  }
  if(i != 2){
    std::cerr<<"Usage: export var"<<std::endl;
    return 1;
  }
  std::string str1 (argArray[1]);
  std::map<std::string,std::string>::iterator it;
  it = mymap.find(str1);
  if(it != mymap.end()){     //if found
    std::string str2 = it->second;  // str2 = var's paired value
    setenv(argArray[1],str2.c_str(),1); //use setenv(var,value,1) to put var=value in environ
  }

  return 1;
}
