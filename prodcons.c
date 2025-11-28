/* prodcons.c */
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define PRODUCERS 2
#define CONSUMERS 2
#define ITEMS_PER_PRODUCER 3

int buffer[BUFFER_SIZE];
int in = 0;  // next position for producer
int out = 0; // next position for consumer

sem_t empty; // counts empty slots
sem_t full;  // counts full slots
pthread_mutex_t mutex;

void* producer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < ITEMS_PER_PRODUCER; ++i) {
        int item = id * 100 + i;

        sem_wait(&empty);             // wait for empty slot
        pthread_mutex_lock(&mutex);   // protect buffer

        buffer[in] = item;
        printf("Producer %d produced item %d at position %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);              // signal that an item is available

        sleep(1); // simulate production time
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*)arg;
    for (int i = 0; i < ITEMS_PER_PRODUCER; ++i) { // each consumer consumes same number for demo
        sem_wait(&full);              // wait for item
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        printf("Consumer %d consumed item %d from position %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);             // signal that a slot is free

        sleep(2); // simulate consumption time (slower consumer)
    }
    return NULL;
}

int main() {
    pthread_t prod[PRODUCERS], cons[CONSUMERS];
    int idsP[PRODUCERS], idsC[CONSUMERS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (int i = 0; i < PRODUCERS; ++i) {
        idsP[i] = i + 1;
        pthread_create(&prod[i], NULL, producer, &idsP[i]);
    }
    for (int i = 0; i < CONSUMERS; ++i) {
        idsC[i] = i + 1;
        pthread_create(&cons[i], NULL, consumer, &idsC[i]);
    }

    for (int i = 0; i < PRODUCERS; ++i) pthread_join(prod[i], NULL);
    for (int i = 0; i < CONSUMERS; ++i) pthread_join(cons[i], NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);
    return 0;
}
