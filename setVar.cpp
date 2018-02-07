#include "setVar.h"
#include <cstdlib>
#include <stdio.h>
#include <cctype>
#include <iostream>
/*       This function implements set command
         if the var name user types in has characters other than letters,underscore,and numbers
         we send error info to user and tell them to input right classes of characters
         two situations
         1. input set var:        we add or update(if exist) <var,""> into mymap
         2. input set var value:  we add or update(if exist) <var,value> into mymap
 */
int setVar(char** argArray, std::map<std::string,std::string> &mymap) {
  std::string strEmpty("");
  int i = 0;
  while(argArray[i] != NULL) {
    i++;
  }
  if((i != 3)&&(i != 2)){
    std::cerr<<"Usage: set var value"<<std::endl;
    return 1;
  }
  std::string temp(argArray[1]);
  const char* underscore = "_";
  for(size_t j =0; j< temp.length(); j++){
    if( (isalnum(temp[j]) == 0) && (temp[j] != *underscore) ){
      std::cerr<<"Variable must be a combination of letters,underscores,and numbers"<<std::endl;
      return 1;
    }
  }
  if( i == 2){
    std::string str1 (argArray[1]);
    std::map<std::string,std::string>::iterator it;
    it = mymap.find(str1);
    if(it != mymap.end()){     //if found
      it->second = strEmpty;
    }
    else{                     //if not found, update mymap
      mymap.insert (std::pair<std::string,std::string>(str1,strEmpty));
    }
  }

  if( i == 3){
    std::string str2 (argArray[1]);
    std::string str3 (argArray[2]);
    std::map<std::string,std::string>::iterator it;
    it = mymap.find(str2);
    if(it != mymap.end()){     //if found
      it->second = str3;
    }
    else{                     //if not found, update mymap
      mymap.insert (std::pair<std::string,std::string>(str2,str3));
    }
  }

  return 1;
}
  
