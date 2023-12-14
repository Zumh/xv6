#include "kernel/types.h"
#include "user/user.h"
// ex8.c : communication between two processes 
//

int main(void){
  int fds[2];
  char buf[100];
  int n, pid;

  // create a pipe, with two FDs in fds[0], fds[1]
  pipe(fds);
  
  pid = fork();
  if (pid == 0){
    // child processes created after parent which is else scope
    // we write to the writing end of a pipe
    write(fds[1], "this is ex8\n", 12);
  } else {
    // parent process
    // read from the pipe of reading end
    n = read(fds[0], buf, sizeof(buf));

    // display the results on the terminal
    // by writing to standard out put
    write(1, buf, n);
  }
  exit(0);
}
