#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"


void find(char command[]){
  // try to find all the file name inside current directory
  // if couldn't then go to the next directory if exist
  // if there is no directory then simply return false and declare files cannot find
}
int main(int argc, char argv[]){
  // get the file name from argument
  if (argc == 3){
    find(argv);
    exit(0);
  }

  printf("couldn' find the file\n");
  exit(-1);
}
