//catchsignal.c:
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void signal_handler(int signum) {
    printf("Signal %d received\n", signum);
}

int main(){
	if (signal(SIGINT, signal_handler) == SIG_ERR) {
            		perror("signal");
            		return 1;
        	}
	
    printf("Waiting for signals...\n");
    while (1) {
        pause();
    }

    return 0;
}
