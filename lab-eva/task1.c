//Write a C program that demonstrates and fixes a race condition:

 //1.    Create a shared global variable                   initialized to 0

//2.  Create 3 threads, each thread increments

//3.  First version WITHOUT mutex:

  //Create and run the 3 threads

//1000 times in a loop

  //Print the final counter value

  //Run multiple times and observe inconsistent results

//4.  Second version WITH mutex:

  //Use mutex to protect the counter increment   Create and run the 3 threads

   //Print the final counter value (should always be 3000)

 //Requirements:
 // Show both versions (with and without mutex) Add comments explaining why mutex is needed Properly initialize and destroy mutex

// Name: Hadia Anjum
// Reg#: 23-NTU-CS-1161

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int counter = 0;            //shared global variable
pthread_mutex_t lock;       //mutex for version

void* add_without_mutex(void* arg) {
    for (int i = 0; i < 1000; i++) {
        counter++;       //race condition can happen   
    }
    return NULL;
}

void* add_with_mutex(void* arg) {
    for (int i = 0; i < 1000; i++) {
        pthread_mutex_lock(&lock);   //lock before updating counter
        counter++;
        pthread_mutex_unlock(&lock);   //unlock after done
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3;
    counter=0;
    pthread_create(&t1, NULL, add_without_mutex, NULL);
    pthread_create(&t2, NULL, add_without_mutex, NULL);
    pthread_create(&t3, NULL, add_without_mutex, NULL);

    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    pthread_join(t3,NULL);     
  
    printf("\nWithout Mutex: Final counter = %d\n", counter);
    printf("Result changes every run (race condition)\n");

    counter = 0;                      
    pthread_mutex_init(&lock, NULL);     //initialize mutex

    pthread_create(&t1, NULL, add_with_mutex, NULL);
    pthread_create(&t2, NULL, add_with_mutex, NULL);
    pthread_create(&t3, NULL, add_with_mutex, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    printf("\nWith Mutex: Final counter = %d\n", counter);
    printf("Always correct result (3000) because mutex avoids race condition\n");

    pthread_mutex_destroy(&lock);      //clear mutex
    return 0;
}
