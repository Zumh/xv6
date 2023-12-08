/*
 * project: xv6/user
 * file: sleep.c file
 * description: 
 Implement a user-level sleep program for xv6, along the lines of the UNIX sleep command. Your sleep should pause for a user-specified number of ticks. A tick is a notion of time defined by the xv6 kernel, namely the time between two interrupts from the timer chip. Your solution should be in the file user/sleep.c.
*/

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[])
{
  if(argc < 2){
    printf("sleep <input number>\n"); 
    exit(-1);
  }

  // get the numer and convert that number to integer and use sleep function
  sleep(atoi(argv[1]));
 exit(0); 
}
