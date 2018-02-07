#include "exportVar.h"
#include "setVar.h"
#include "analyse.h"
#include "startRun.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include <cstdlib>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <map>
#include "cd.h"
/*      myShell.cpp contains main funciton
 */
int runCommand(char** argArray, std::map<std::string,std::string> &mymap){
  if (argArray[0] == NULL){     // if user only click 'return', the'\n' is removed, so argArray[0] is NULL
    return 1;
  }
  if (strcmp(argArray[0], "set") == 0){          //if first argument is  'set'
    return setVar(argArray,mymap);
  }
  if (strcmp(argArray[0], "export") == 0){        //export
    return exportVar(argArray,mymap);
  }
  if (strcmp(argArray[0], "cd") == 0){          //cd
    return cd(argArray);
  }
  if (strcmp(argArray[0], "exit") == 0) {         //exit
    return 0;
  }
  return startRun(argArray);  //startRun.cpp
}

int main(){
  int status = 1;
  std::map<std::string,std::string> mymap;
  char** argArray;
  while(status){      //while(status = 1), myShell prompt will keep showing, until status is updated to 0

    char* buf = NULL;
    size_t size = 0;
    buf = getcwd( buf, size);     //get current directory
    std::cout << "myShell:"<<buf<<" $";  //print current directory after myShell:
    char* cmdline = NULL;
    size_t sz;
    if(getline(&cmdline, &sz, stdin) >= 0){    //getline from stdin
      argArray = analyse(cmdline,mymap);            //analyse.cpp
      status = runCommand(argArray,mymap);          
    }
   
    // std::cout<<mymap.size()<<std::endl;
    int i = 0;
    while (argArray[i] != NULL){
      free(argArray[i]);     //free 
      i++;
    }
    free(argArray[i]);  
    free(argArray);
    free(cmdline);
    free(buf);
  }
  return 0;
}
