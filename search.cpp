#include "search.h"
#include <stdio.h>
#include <cstdlib>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <string>
#include <iostream>

/*    This function is abstracted out to fit two conditions in startRun.cpp.   

      1. If pathname doesn't have '/', then we use this function to search for the program in each
      directory listed in pathVector returned by makePathVector().

      2. If pathname has '/', then we make a new pathVector with only the current directory
      and also use this function to search for the program only in this directory.

      if cannot find the program, RETURN "Failed to find progName" 
      This specific string will be checked by startRun(...) which calls search(...) 
*/

std::string search(std::string progName, std::vector<std::string> pathVector) {
  DIR *pDIR;
  struct dirent *entry;
  for (std::vector<std::string>::iterator it = pathVector.begin(); it != pathVector.end(); ++it) {
    if( (pDIR=opendir( (*it).c_str()  )  ) != NULL) {
      while( (entry = readdir(pDIR)) != NULL) {
	std::string entryName(entry->d_name);
	if( ( entryName.compare(".") != 0)&& (entryName.compare("..") != 0) ){
	  if(progName.compare(entryName) == 0) {   //if found
	    if(pathVector.size() == 1) {               //condition 2 in the description at front
	      std::string progPath = *it + progName;
	      closedir(pDIR);
	      return progPath;
	    }
	    else {         //condition 1 in the description at front
	      std::string progPath = *it + "/" + progName;
	      closedir(pDIR);
	      return progPath;
	    }
	  } // end if found
	}
      }
      closedir(pDIR);
    }
    else{   // if failed to opendir
      std::cerr<<"Failed to open the directory "<< (*it) <<std::endl;
    }
  }// end iterate
  std::string msg ("Failed to find progName");
  return msg;
}
	     
