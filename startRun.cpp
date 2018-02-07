#include "startRun.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
#include <string>
#include <iostream>
#include "makePathVector.h"
#include "search.h"

int startRun(char** argArray) {    //command will be 1st input of execve
  char* command = argArray[0]; //if argArray[0] doesn't have '/', command = result of search()
                               //else, command = argArray[0]
  if (strchr(argArray[0], '/') == NULL) {   // if argArray[0] doesn't have '/' in it
    std::string progName(argArray[0]);
    std::vector<std::string> pathVector = makePathVector();

    /*    for (std::vector<std::string>::iterator it = pathVector.begin(); it != pathVector.end(); ++it){
	std::cout<<(*it)<<std::endl;
	}// This is for testing  */ 
    std::string progPath = search(progName,pathVector);
    command = (char*)progPath.c_str();  //update the command
    if (progPath.compare("Failed to find progName") == 0){
      std::cout<<"Command "<<argArray[0]<<" not found"<<std::endl;
      return 1;
    }
  }
  else {    // if argArray[0] has '/' in it
    char* ptr = strrchr(argArray[0],'/');    //find the pos of last '/'
    char* temp1 = strdup(ptr + 1);
    std::string progName(temp1);
    char* temp2 = strndup(argArray[0], ptr+1-argArray[0]);//get 'path/' before the progName
    std::string path1(temp2);
    std::vector<std::string> pathVector;
    pathVector.push_back(path1);
    std::string progPath = search(progName,pathVector);
    if (progPath.compare("Failed to find progName") == 0){
      std::cout<<"Command "<<argArray[0]<<" not found"<<std::endl;
      free(temp1);
      free(temp2);
      return 1;
    }
    free(temp1);
    free(temp2);
  } //end else
    
  /******** The following code is from man waitpid  ******/
  pid_t cpid, w;
  int status;
  cpid = fork();
  if (cpid == -1) {
    perror("fork");
    exit(EXIT_FAILURE);
  }

  if (cpid == 0) {            /* Code executed by child */
    if (execve(command, argArray, environ) == -1) {
      perror("execve");
      exit(50);
    }

  } else {                    /* Code executed by parent */
    do {
      w = waitpid(cpid, &status, WUNTRACED );
      if (w == -1) {
	perror("waitpid");
	exit(EXIT_FAILURE);
      }
      if (WIFEXITED(status)) {
	if (WEXITSTATUS(status) == 50) {
	  return 1;
	}
	printf("Program exited with status %d\n", WEXITSTATUS(status));
      } else if (WIFSIGNALED(status)) {
	printf("Program was killed by signal %d\n", WTERMSIG(status));
      }      
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));   
  }
  return 1;
}
       
