#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t resource_semaphore;

void* thread_function(void* arg) {
    int id = *(int*)arg;

    printf("Thread %d: Waiting for resource...\n", id);
    sem_wait(&resource_semaphore);

    printf("Thread %d: Acquired resource!\n", id);
    sleep(2);

    printf("Thread %d: Releasing resource...\n", id);
    sem_post(&resource_semaphore);

    return NULL;
}

int main() {
    pthread_t threads[5];
    int ids[5];

    sem_init(&resource_semaphore, 0, 3);

    for (int i = 0; i < 5; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, thread_function, &ids[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    sem_destroy(&resource_semaphore);
    return 0;
}
