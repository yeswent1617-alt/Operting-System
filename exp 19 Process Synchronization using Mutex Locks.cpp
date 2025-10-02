/* 
 ============================================================================
    C Program to Demonstrate Process Synchronization using Mutex Locks
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int shared_counter = 0;           // Shared resource
pthread_mutex_t lock;             // Mutex lock

// Function executed by threads
void* increment(void* arg) {
    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&lock);        // Acquire lock (enter critical section)

        int temp = shared_counter;
        printf("Thread %ld entered critical section. Counter = %d\n", pthread_self(), temp);
        temp++;
        sleep(1);  // Simulate some work
        shared_counter = temp;
        printf("Thread %ld updated counter to %d\n", pthread_self(), shared_counter);

        pthread_mutex_unlock(&lock);      // Release lock (exit critical section)

        sleep(1);  // Give chance to other thread
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    // Initialize mutex
    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex initialization failed.\n");
        return 1;
    }

    // Create two threads
    pthread_create(&t1, NULL, increment, NULL);
    pthread_create(&t2, NULL, increment, NULL);

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    // Destroy mutex
    pthread_mutex_destroy(&lock);

    printf("\nFinal value of shared counter: %d\n", shared_counter);
    return 0;
}

