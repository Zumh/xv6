/*
 * file: pingpong.c
 * description: 
 *Write a user-level program that uses xv6 system calls to ''ping-pong'' a byte between two processes over a pair of pipes, one for each direction. The parent should send a byte to the child; the child should print "<pid>: received ping", where <pid> is its process ID, write the byte on the pipe to the parent, and exit; the parent should read the byte from the child, print "<pid>: received pong", and exit. Your solution should be in the file user/pingpong.c.
 * */

 #include "kernel/types.h" 
 #include "kernel/stat.h"
 #include "user/user.h"

int main(void){
  // create file descriptor
  // pipe
  // fork
  int fd[2] = {0};
  char childToParent[20] = "pong";
  char parentToChild[20] = "ping";
  pipe(fd);
  int pid = fork();
  // here we decide the parent and child action on how to send message
  if (pid == 0){
    // child process 
    // after forking a child pid will be zero and process action in this scope 
    char message[20] = "";

    read(fd[0], message, sizeof(message));
    printf("%d: received %s\n", getpid(), message);

    // close the reading and response to the parent
    close(fd[0]);
    write(fd[1], childToParent, sizeof(childToParent));
    close(fd[1]);
    // we end or release the child process after all the action
    exit(0);
  } else {
    char message[20] = "";
    write(fd[1], parentToChild, sizeof(parentToChild));
    close(fd[1]);

    // we wait for child to finish tasks
    wait(0);
    read(fd[0], message, sizeof(message));
    printf("%d: received %s\n", getpid(), message);
    close(fd[0]);
  }
  exit(0);
}
