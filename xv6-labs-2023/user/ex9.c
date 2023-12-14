#include "kernel/types.h"
#include "user/user.h"
// ex9.c : list file names in the current directory 
//
struct dirent {
  ushort inum;
  char name[14];
};
int main(void){
  int fd;
  struct dirent e;
  
  fd = open(".", 0);
  // read all the file names form current folder and print them
  // until there is no more file names left to read
  while(read(fd, &e, sizeof(e)) == sizeof(e)){
    if(e.name[0] != '\0'){
      printf("%s\n", e.name);
    }
  }
  exit(0);
}
