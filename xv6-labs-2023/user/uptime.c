/*#include "kernel/types.h"
#include "user/user.h"
#include "kernel/defs.h"
int main(int argc, char *argv[]){
	//initialize the tick
	int prev = read_tick();
	int current = 0;

	// make a loop keep running and calculate the up time in seconds
	while(1){
		current = read_ticks();
		uptime = (current - prev)/100;
		printf("%d\n", uptime);
		prev = current;
		sleep(1000);
	}
	exit(0);
}*/
