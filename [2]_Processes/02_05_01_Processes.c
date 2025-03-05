//another.c:
#include <stdio.h>

int main() {
    printf("Hello, I'm another program!\n");
    getchar();
    return 0;
}


//Użycie poleceń systemowych takich jak ps czy htop pozwala obserwować przejście z programu exec do innego programu.cc. 
//Identyfikator procesu (PID) i inne szczegóły zmieniają się, aby odzwierciedlić nowy proces utworzony przez funkcję execl().

