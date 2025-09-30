#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define N 5  // Number of philosophers

pthread_mutex_t chopsticks[N]; // Mutexes representing chopsticks

void* philosopher(void* num) {
    int id = *(int*)num;

    for (int i = 0; i < 3; i++) { // Each philosopher eats 3 times
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3 + 1); // Thinking

        // Pick up chopsticks
        if (id % 2 == 0) {
            // Even philosopher picks left then right
            pthread_mutex_lock(&chopsticks[id]);
            pthread_mutex_lock(&chopsticks[(id + 1) % N]);
        } else {
            // Odd philosopher picks right then left
            pthread_mutex_lock(&chopsticks[(id + 1) % N]);
            pthread_mutex_lock(&chopsticks[id]);
        }

        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 2 + 1); // Eating

        // Put down chopsticks
        pthread_mutex_unlock(&chopsticks[id]);
        pthread_mutex_unlock(&chopsticks[(id + 1) % N]);

        printf("Philosopher %d finished eating and starts thinking again.\n", id);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    // Initialize chopsticks (mutexes)
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
        ids[i] = i;
    }

    // Create philosopher threads
    for (int i = 0; i < N; i++) {
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Wait for all philosophers to finish
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutexes
    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    printf("Dinner is over. All philosophers have finished eating.\n");
    return 0;
}

