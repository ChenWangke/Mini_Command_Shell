#include "interpretVar.h"

/*     This function evaluates the argString
       if it stsrts with $, then we search for the string after '$' in mymap's variable list
       if found, we replace the argString with the value paired to it  
       and return the new argString    
       RETURN VALUE: update std::string argString by its paired value in mymap    
*/
std::string interpretVar(std::string argString, std::map<std::string,std::string> mymap) {
  if(argString[0] == '$'){
    std::string str1 = argString.substr(1);    //str1:   string after'$' in argstring
    std::map<std::string,std::string>::iterator it;
    it = mymap.find(str1);
    if(it != mymap.end()){     //if found
      return it->second;
    }
  }
  return argString;
}
       
