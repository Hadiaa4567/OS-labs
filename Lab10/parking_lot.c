/* parking_lot.c */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>

sem_t parking_spaces;

void* car(void* arg) {
    int id = *(int*)arg;
    free(arg); // we allocated it in main
    printf("Car %d is trying to park...\n", id);

    sem_wait(&parking_spaces); // wait for a space
    printf("Car %d parked successfully!\n", id);
    sleep(2); // simulate being parked
    printf("Car %d is leaving.\n", id);

    sem_post(&parking_spaces); // free the space
    return NULL;
}

int main() {
    const int NUM_CARS = 10;
    const int NUM_SPACES = 3;
    pthread_t cars[NUM_CARS];

    sem_init(&parking_spaces, 0, NUM_SPACES);

    for (int i = 0; i < NUM_CARS; ++i) {
        int *id = malloc(sizeof(int));
        *id = i + 1;
        if (pthread_create(&cars[i], NULL, car, id) != 0) {
            perror("pthread_create");
            return 1;
        }
    }

    for (int i = 0; i < NUM_CARS; ++i) {
        pthread_join(cars[i], NULL);
    }

    sem_destroy(&parking_spaces);
    return 0;
}