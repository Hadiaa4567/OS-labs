#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

// Function executed by each thread
void* threadFunction(void* arg) {
    int threadNum = *(int*)arg;  // Thread number
    pthread_t threadID = pthread_self();  // Get thread ID

    printf("Thread %d started. Thread ID: %lu\n", threadNum, threadID);

    // Sleep for random time between 1 to 3 seconds
    int sleepTime = (rand() % 3) + 1;
    sleep(sleepTime);

    printf("Thread %d (ID: %lu) completed after %d seconds.\n", threadNum, threadID, sleepTime);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadNums[NUM_THREADS];

    srand(time(NULL));  // Seed for random number generator

    for (int i = 0; i < NUM_THREADS; i++) {
        threadNums[i] = i + 1;
        pthread_create(&threads[i], NULL, threadFunction, &threadNums[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed.\n");
    return 0;
}


