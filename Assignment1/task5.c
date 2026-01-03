#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>

// Define Student structure
typedef struct {
    int student_id;
    char name[50];
    float gpa;
} Student;

// Shared variable for counting Dean’s List students
int deans_list_count = 0;
pthread_mutex_t mutex;

// Thread function
void* check_deans_list(void* arg) {
    Student s = *(Student*)arg; // copy the data locally
    free(arg); // free dynamically allocated memory

    printf("\nStudent ID: %d\n", s.student_id);
    printf("Name: %s\n", s.name);
    printf("GPA: %.2f\n", s.gpa);

    if (s.gpa >= 3.5) {
        printf("Status: 🎓 On Dean's List!\n");

        pthread_mutex_lock(&mutex);
        deans_list_count++;
        pthread_mutex_unlock(&mutex);
    } else {
        printf("Status: Not on Dean's List.\n");
    }

    return NULL;
}

int main() {
    pthread_t threads[3];
    pthread_mutex_init(&mutex, NULL);

    // Create 3 sample students
    Student students[3] = {
        {101, "Ayeza", 3.8},
        {102, "Hadia", 3.2},
        {103, "Areeba", 3.6}
    };

    // Create one thread per student (each gets its own copy)
    for (int i = 0; i < 3; i++) {
        Student* s = malloc(sizeof(Student)); // allocate separate memory
        *s = students[i];                     // copy struct
        pthread_create(&threads[i], NULL, check_deans_list, (void*)s);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\nTotal students on Dean's List: %d\n", deans_list_count);

    pthread_mutex_destroy(&mutex);
    return 0;
}

