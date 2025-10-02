/* 
 ============================================================================
    C Program to Simulate Reader-Writer Problem using Semaphores
 ============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t mutex;      // Semaphore to protect read_count
sem_t wrt;        // Semaphore for writer (write lock)
int read_count = 0; // Number of readers currently reading
int shared_data = 0; // Shared resource

// Reader function
void* reader(void* arg) {
    int id = *((int*)arg);

    sem_wait(&mutex);          // Lock access to read_count
    read_count++;
    if (read_count == 1)
        sem_wait(&wrt);        // First reader blocks writers
    sem_post(&mutex);

    // Critical Section (Reading)
    printf("Reader %d is reading shared_data = %d\n", id, shared_data);
    sleep(1);

    sem_wait(&mutex);
    read_count--;
    if (read_count == 0)
        sem_post(&wrt);        // Last reader allows writers
    sem_post(&mutex);

    pthread_exit(NULL);
}

// Writer function
void* writer(void* arg) {
    int id = *((int*)arg);

    sem_wait(&wrt);           // Wait for exclusive access
    shared_data += 10;        // Modify shared resource
    printf("Writer %d updated shared_data to %d\n", id, shared_data);
    sleep(1);
    sem_post(&wrt);           // Release lock

    pthread_exit(NULL);
}

int main() {
    pthread_t r[5], w[3];
    int r_id[5], w_id[3];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    sem_init(&wrt, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        r_id[i] = i + 1;
        pthread_create(&r[i], NULL, reader, &r_id[i]);
    }

    // Create writer threads
    for (int i = 0; i < 3; i++) {
        w_id[i] = i + 1;
        pthread_create(&w[i], NULL, writer, &w_id[i]);
    }

    // Join threads
    for (int i = 0; i < 5; i++)
        pthread_join(r[i], NULL);
    for (int i = 0; i < 3; i++)
        pthread_join(w[i], NULL);

    // Destroy semaphores
    sem_destroy(&mutex);
    sem_destroy(&wrt);

    printf("\nFinal value of shared_data: %d\n", shared_data);

    return 0;
}

