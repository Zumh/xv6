/*
 * file: primes.c
 * description:
 *Write a concurrent prime sieve program for xv6 using pipes and the design illustrated in the picture halfway down this page and the surrounding text. This idea is due to Doug McIlroy, inventor of Unix pipes. Your solution should be in the file user/primes.c
 * */

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void handlePrime(int fd[]);

int main(void){
  // create initial fd pipe and parent process for generating number 2-35
  int fd[2] = {0};
  if (pipe(fd) < 0){
    exit(-1);
  }
  int pid = fork();
  if(pid < 0){
    exit(-1);
  } else if (pid == 0){

    // process children
    // call function for handling child process
    handlePrime(fd);
    // after done with processing we release the process immediately
    exit(0);
  } else {
    // process parent
    close(fd[0]);
    // filled created pipe with number 2 - -35
    for(int number = 2; number <= 35; number++){
      write(fd[1], &number, sizeof(int));

    }
    close(fd[1]);

    // wait for child to get things done
    wait(0);
    // we close the reading end of pipe after processing the date in child process
  }
  // success
  exit(0);
}

void handlePrime(int fd[]){
  // close write end for reading end 
  close(fd[1]);
  int newfd[2] = {-1}; 
  int prime = 0, nextPrime = 0;
  read(fd[0], &prime, sizeof(prime));

  printf("prime %d\n", prime);
  // read return zero when nothing else to read and write end is close
  while(read(fd[0], &nextPrime, sizeof(int))> 0){
    if (nextPrime%prime != 0){
      // we made sure that we create processs and assum that the number is prime.
      
      if (newfd[0] < 0){
        pipe(newfd);                                                                                       
        int pid = fork();
        if (pid < 0){
          // if fail to pipe
          exit(-1);
        } else if (pid == 0){
          handlePrime(newfd);
           // as soon as the child processing and return from the function we exit to relase the process.
          exit(0);
        }
      }

      if (write(newfd[1], &nextPrime , sizeof(int)) == -1 ){
        exit(-1);
      }

    }
  }
  close(newfd[1]);
  wait(0);
  close(newfd[0]);
}

