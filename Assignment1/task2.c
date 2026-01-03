#include <stdio.h>
#include <pthread.h>
#include <string.h>

// Thread function
void* greeting(void* arg) {
    char* name = (char*)arg;  // Receive name argument
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_id;
    char name[50];

    printf("Enter your name: ");
    scanf("%s", name);

    // Create thread
    pthread_create(&thread_id, NULL, greeting, (void*)name);

    printf("Main thread: Waiting for greeting...\n");

    // Wait for the created thread to finish
    pthread_join(thread_id, NULL);

    printf("Main thread: Greeting completed.\n");
    return 0;
}

