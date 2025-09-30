#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// Function to be executed by thread 1
void* threadFunction1(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread 1: Count %d\n", i);
        sleep(1);  // simulate work
    }
    pthread_exit(NULL);
}

// Function to be executed by thread 2
void* threadFunction2(void* arg) {
    for (int i = 0; i < 5; i++) {
        printf("Thread 2: Count %d\n", i);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t t1, t2;

    // Create threads
    if (pthread_create(&t1, NULL, threadFunction1, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    if (pthread_create(&t2, NULL, threadFunction2, NULL) != 0) {
        perror("pthread_create");
        exit(EXIT_FAILURE);
    }

    // Wait for threads to finish
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("Main: All threads finished execution.\n");

    return 0;
}

