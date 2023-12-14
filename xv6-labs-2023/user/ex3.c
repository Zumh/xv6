// ex3.c: create a new process with fork()

#include "kernel/types.h"
#include "user/user.h"

int main(void) {
  int pid = 0;

  pid = fork();

  printf("fork() returned %d\n", pid);

  if(pid == 0){
    printf("child\n");
  } else {
    printf("parent\n");
  }

  exit(0);
}
