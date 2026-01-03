#include <stdio.h>
#include <pthread.h>

// Thread function
void* numberInfo(void* arg) {
    int num = *(int*)arg;  // Get integer from argument
    printf("Thread: Number = %d\n", num);
    printf("Thread: Square = %d\n", num * num);
    printf("Thread: Cube = %d\n", num * num * num);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread_id;
    int number;

    printf("Enter an integer: ");
    scanf("%d", &number);

    // Create thread and pass number as argument
    pthread_create(&thread_id, NULL, numberInfo, (void*)&number);

    // Wait for thread to finish
    pthread_join(thread_id, NULL);

    printf("Main thread: Work completed.\n");
    return 0;
}

