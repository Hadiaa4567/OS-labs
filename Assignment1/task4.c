#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Thread function to compute factorial
void* factorial(void* arg) {
    int n = *(int*)arg;
    unsigned long long* result = malloc(sizeof(unsigned long long)); // allocate memory for result
    *result = 1;

    for (int i = 1; i <= n; i++) {
        *result *= i;
    }

    pthread_exit((void*)result); // return result pointer
}

int main() {
    pthread_t thread;
    int num;
    unsigned long long* result;

    printf("Enter a number: ");
    scanf("%d", &num);

    // Create thread
    pthread_create(&thread, NULL, factorial, &num);

    // Wait for thread to finish and get return value
    pthread_join(thread, (void**)&result);

    printf("Factorial of %d is: %llu\n", num, *result);

    free(result); // free allocated memory
    return 0;
}

