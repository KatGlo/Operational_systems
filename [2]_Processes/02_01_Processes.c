#include <stdio.h>
#include <unistd.h>

int main() {

    printf("Parent PID: %d\n", getpid());
    getchar();

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        printf("Child PID: %d, Parent PID: %d\n", getpid(), getppid());
        getchar();
    } else {
        getchar();
    }

    return 0;
}
