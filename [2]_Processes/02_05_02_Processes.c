//exec.c:
#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Hello, I'm exec program!\n");
    getchar(); 
    execl("./another", "another", (char *)NULL);
    perror("exec");
    return 1;
}

//Użycie poleceń systemowych takich jak ps czy htop pozwala obserwować przejście z programu exec do innego programu.cc. 
//Identyfikator procesu (PID) i inne szczegóły zmieniają się, aby odzwierciedlić nowy proces utworzony przez funkcję execl().

