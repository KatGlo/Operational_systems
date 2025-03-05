#include <stdio.h>
#include <unistd.h>

void showProcessInfo(const char *label) {
    printf("%s PID: %d, PPID: %d\n", label, getpid(), getppid());
}

int main() {

    showProcessInfo("Parent");
    getchar();

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("Fork failed");
        return 1;
    }

    if (child_pid == 0) {
        showProcessInfo("First Child");
        getchar();
        pid_t grandchild_pid = fork();

        if (grandchild_pid == -1) {
            perror("Fork failed");
            return 1;
        }

        if (grandchild_pid == 0) {
            showProcessInfo("Grandchild");
            getchar();
        }
    } else {
        getchar();
    }

    return 0;
}
