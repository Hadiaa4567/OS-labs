#include <stdio.h>
#include <pthread.h>

void* print_number(void* arg) {
    int num = *(int*)arg; // Cast void* back to int*
    int doubled = num * 2; // CGP doubled

    printf("Thread received CGP: %d\n", num);
    printf("Doubled CGP: %d\n", doubled);

    return NULL;
}

int main() {
    pthread_t thread_id;
    int cgp = 3.2; // Original CGP

    printf("Creating thread with CGP: %d\n", cgp);

    // Pass address of 'cgp' to thread
    pthread_create(&thread_id, NULL, print_number, &cgp);

    pthread_join(thread_id, NULL);
    printf("Main thread done.\n");

    return 0;
}
