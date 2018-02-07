#include <cstdlib>
#include <string.h>
#include "makePathVector.h"
#include <string>
#include <vector>
#include <stdio.h>

/*    Since PATH environment variable is colon delimited list of paths
      This function seperates the list of paths and put each path into 
      a vector<string> pathVector   
      RETURN VALUE: pathVector             
*/
std::vector<std::string> makePathVector() {
  std::vector<std::string> pathVector;
  char* pth;
  char* pathString = getenv("PATH");
  char* temp = new char[strlen(pathString)+1];   //copy pathString to temp, 
  strcpy(temp,pathString);       //because we don't want strsep modify pathString
  char* tempbegin = temp;     //make a pointer tempbegin point to begin of temp,for later delete
  pth = strsep(&temp,":");
  while(pth != NULL){
    std::string pthString(pth);
    pathVector.push_back(pthString);
    pth = strsep(&temp,":");
  }
  delete []tempbegin;  //delete temp
  return pathVector;
}
