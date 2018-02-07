/*    This print.cpp is for testing   */
#include <stdio.h>
#include <cstdlib>

int main(int argc, char** argv){
  if(argc <= 1){
    printf("Usage: print args\n");
    return EXIT_FAILURE;
  }
  for(int i = 0; i < argc; i++){
    printf("'%s'\n",argv[i]);
  }

  return EXIT_SUCCESS;
}
