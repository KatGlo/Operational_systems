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
        pid_t grandchild_pid_1 = fork();

        if (grandchild_pid_1 == -1) {
            perror("Fork failed");
            return 1;
        }

        if (grandchild_pid_1 == 0) {
            showProcessInfo("First Grandchild");
            getchar();
        }
    } else {
        getchar();
        pid_t child_pid_2 = fork();

        if (child_pid_2 == -1) {
            perror("Fork failed");
            return 1;
        }

        if (child_pid_2 == 0) {
            showProcessInfo("Second Child");
            getchar();
            pid_t grandchild_pid_2 = fork();

            if (grandchild_pid_2 == -1) {
                perror("Fork failed");
                return 1;
            }

            if (grandchild_pid_2 == 0) {
                showProcessInfo("Second Grandchild");
                getchar();
            }
        }
    }

    return 0;
}
