#include "kernel/types.h"
#include "user/user.h"
// ex7.c : communication over a pipe
//

int main(void){
  int fds[2];
  char buf[100];
  int n;

  // create a pipe, with two FDs in fds[0], fds[1]
  pipe(fds);

  // write to the pipe from the writing end of the pipe
  write(fds[1], "xyz\n", 4);

  // read from the pipe of reading end
  n = read(fds[0], buf, sizeof(buf));

  // display the results on the terminal
  // by writing to standard out put
  write(1, buf, n);

  exit(0);
}
