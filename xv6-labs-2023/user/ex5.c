// ex5.c fork then exec
#include "kernel/types.h"
#include "user/user.h"

int main(void){
  int pid = 0 , status;
  pid = fork();
  if(pid == 0 ){// child process
    char *argv[] = {"echo", "THIS", "IS", "ECHO", 0};

    exec(argv[0], argv);
    printf("exe failed!\n");
    exit(1);
  } else {// parent process

    printf("parent waiting\n");
    wait(&status);
    printf("the child exited with status %d\n", status);
  }
  exit(0);
}
