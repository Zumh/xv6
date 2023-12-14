#include "kernel/types.h"
#include "user/user.h"

// ex1.c : copy input to output
int main(void) {
  // simple reading from stdin and write it back from system to user
  char buf[64];
  int n = 0;
  while(1){
    // 0 mean reading flag
    if((n = read(0, buf, sizeof(buf)))<=0){
      break;
    }
    // 1 mean writing flag
    write(1, buf, n);
  }

  // release all the remaining resources that we used
  exit(0);
}

