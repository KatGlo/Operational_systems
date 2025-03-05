#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Hello, I'm system program!\n");
    getchar();  // Stop execution

    int result = system("ls -al /var/log/");

    if (result == -1) {
        perror("system");
        return 1;
    }

    return 0;
}

