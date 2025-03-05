//sendsignal.c:

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <PID> <signal>\n", argv[0]);
        return 1;
    }

    pid_t dest_pid = atoi(argv[1]);
    int signal_num = atoi(argv[2]);

    if (kill(dest_pid, signal_num) == -1) {
        perror("kill");
        return 1;
    }

    printf("Signal %d sent to process %d\n", signal_num, dest_pid);

    return 0;
}


