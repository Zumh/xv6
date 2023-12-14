// ex2.c: create a file, write to it.

#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"

int main(void){
  /*The flags O_WRONLY, O_CREATE, and O_TRUNC are used as options for the open() system call:
O_WRONLY: Opens the file for writing only.
O_CREATE: Creates the file if it does not exist.
O_TRUNC: Truncates the file to zero length if it exists.*/
  int fd = open("out", O_WRONLY | O_CREATE | O_TRUNC);

  printf("open returned fd %d\n", fd);

  // 4 represent memory size for the data to write in open file
  // out
  write(fd, "ooo\n", 4);

  exit(0);
}
