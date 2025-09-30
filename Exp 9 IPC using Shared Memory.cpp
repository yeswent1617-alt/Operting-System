#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>   // defines key_t
#include <sys/ipc.h>    
#include <sys/shm.h>     // shmget, shmat, shmdt, shmctl

#define SHM_SIZE 1024  // Size of shared memory

int main() {
    key_t key = 1234;  // fixed key (no ftok needed)

    // Create shared memory segment
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }

    // Attach to shared memory
    char *shm_ptr = (char *)shmat(shmid, NULL, 0);
    if (shm_ptr == (char *)(-1)) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    // Write message
    strcpy(shm_ptr, "Hello, shared memory!");

    // Print message
    printf("Data written to shared memory: %s\n", shm_ptr);

    // Detach from shared memory
    if (shmdt(shm_ptr) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    // Remove shared memory segment
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

