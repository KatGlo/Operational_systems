#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define MAX_PHILOSOPHERS 10

int method_type;
pthread_mutex_t chopsticks[MAX_PHILOSOPHERS];
int philosopher_count;

void pick_chopsticks(int philosopher_number) {
    if (method_type == 1) {
        // Metoda 1: Podnoszenie obu sztućców jednocześnie
        pthread_mutex_lock(&chopsticks[philosopher_number]);
        pthread_mutex_lock(&chopsticks[(philosopher_number + 1) % philosopher_count]);
    } else {
        // Metoda 2: Parzyści i nieparzyści filozofowie podnoszą w różnej kolejności
        if (philosopher_number % 2 == 0) {
            pthread_mutex_lock(&chopsticks[philosopher_number]);
            pthread_mutex_lock(&chopsticks[(philosopher_number + 1) % philosopher_count]);
        } else {
            pthread_mutex_lock(&chopsticks[(philosopher_number + 1) % philosopher_count]);
            pthread_mutex_lock(&chopsticks[philosopher_number]);
        }
    }
}

void put_chopsticks(int philosopher_number) {
    pthread_mutex_unlock(&chopsticks[philosopher_number]);
    pthread_mutex_unlock(&chopsticks[(philosopher_number + 1) % philosopher_count]);
}

void *philosopher(void *num) {
    int id = *(int *)num;

    while (1) {
        printf("Filozof %d myśli...\n", id);
        sleep(rand() % 10 + 1); // Myślenie

        printf("Filozof %d jest głodny...\n", id);
        pick_chopsticks(id);

        printf("Filozof %d je...\n", id);
        sleep(rand() % 10 + 1); // Jedzenie

        put_chopsticks(id);
        printf("Filozof %d skończył jeść.\n", id);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Użycie: ./filozof <typ> <n>\n");
        return 1;
    }

    method_type = atoi(argv[1]);
    philosopher_count = atoi(argv[2]);

    if (philosopher_count < 2 || philosopher_count > MAX_PHILOSOPHERS) {
        printf("Liczba filozofów powinna być w zakresie 2..10\n");
        return 1;
    }

    pthread_t philosophers[MAX_PHILOSOPHERS];
    int ids[MAX_PHILOSOPHERS];

    for (int i = 0; i < philosopher_count; ++i) {
        pthread_mutex_init(&chopsticks[i], NULL);
        ids[i] = i;
    }

    for (int i = 0; i < philosopher_count; ++i) {
        pthread_create(&philosophers[i], NULL, philosopher, (void *)&ids[i]);
    }

    for (int i = 0; i < philosopher_count; ++i) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < philosopher_count; ++i) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}

