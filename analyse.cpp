#include "analyse.h"
#include "interpretVar.h"
#include <string>
#include <string.h>
#include <cstdlib>
#include <stdio.h>
/*     This function interprets the commandline and correctly seperate it into multiple arguments. 
       RETURN VALUE: char** argArray: an array of (char *)string, in which each string is an argument     
*/

char** analyse(char *cmdline, std::map<std::string,std::string> &mymap) {
  char* nptr = strchr(cmdline,'\n');    //remove '\n' in user's input
  *nptr = '\0';
  char** argArray = NULL;
  char* arg = NULL;
  char* ptr;
  std::string argString;
  size_t iSlash = 0;
  size_t i = 0;
  arg = strsep(&cmdline, " ");
  const char *whitespace = " ";
  while (arg != NULL) {
    if (*arg != '\0') {
      //Following code is: if current arg ends with'\', AND if next arg doesn't start with whitespace,
      //we append the next arg to this arg, and replace '\' with whitespace
      if (((ptr = strrchr(arg, '\\')) != NULL)&&(*(ptr+1) == '\0')) {
	if (argString.length() > 0){
	  iSlash = iSlash + (ptr - arg + 1);  
	}
	else {
	  iSlash = iSlash + (ptr - arg);
	}
	argString.append(arg);
	argString.replace(iSlash, 1, " "); //replace '\' with whitespace

	if (*cmdline == *whitespace) { //if next arg start with whitespace
                               //we put current arg into argArray
	  argArray =(char**)realloc(argArray, (i+1) * sizeof(*argArray));
	  argString = interpretVar(argString, mymap);   //evaluate '$' and search it in mymap
	  argArray[i] = strdup(argString.c_str());
	  i++;
	  argString.clear();
	  iSlash = 0;
	}
      } // end if arg ends with'\'
      else {    //if arg doesn't have '\', or arg has'\' but doesn't end with it
	argString.append(arg);
	argArray =(char**)realloc(argArray, (i+1) * sizeof(*argArray));
	argString = interpretVar(argString, mymap);  //evaluate '$' and search it in mymap
	argArray[i] = strdup(argString.c_str());
	i++;
	argString.clear();
	iSlash = 0;
      }
    }// end if *arg !='\0'

    //when there are multiple whitespaces,arg produced by strsep is '\0'
    //so we do next strsep until *arg !='\0'
    arg = strsep(&cmdline," ");
  }// end while
  argArray =(char**)realloc(argArray, (i+1) * sizeof(*argArray));
  argArray[i] = NULL;  //argArray for execve must end with NULL
  return argArray;
}
