#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
// ex6.c: run a command with output redirected
int main(void){
  
  int pid = 0;
  pid = fork();

  if(pid == 0){
    // close the standard output
    close(1); // close the writing end of a pipe
    // we open a file call out for write only mode and crate the file.
    // if alread exist then we truncate to zero length
    open("out", O_WRONLY | O_CREATE | O_TRUNC);
    char *argv[] = {"echo", "this", "is", "redirected", "echo", 0};
    exec(argv[0], argv);
    printf("exec failed!\n");
    exit(1);
  } else {

    wait(0);
  }
  exit(0);
}
