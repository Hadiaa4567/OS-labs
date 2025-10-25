#include <stdio.h>
#include <pthread.h>

typedef struct {
    int id;
    char* name;
    float cgp;
} ThreadData;

// Thread function
void* printData(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    printf("Thread %d:\n", data->id);
    printf("Name: %s\n", data->name);
    printf("CGP: %.2f\n\n", data->cgp);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // Thread data
    ThreadData data1 = {1, "Hadia", 3.75};
    ThreadData data2 = {2, "Hadia", 3.75};

    // Create threads
    pthread_create(&t1, NULL, printData, &data1);
    pthread_create(&t2, NULL, printData, &data2);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("All threads done.\n");
    return 0;
}
