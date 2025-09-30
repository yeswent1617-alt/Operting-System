#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 100

// Message structure
struct message {
    long msg_type;       // Must be > 0
    char msg_text[MSG_SIZE];
};

int main() {
    // Make sure the key file exists
    FILE *fp = fopen("msgqfile", "w");
    if (!fp) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    fclose(fp);

    // Generate a unique key for the message queue
    key_t key = ftok("msgqfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // Create a message queue or get existing
    int msgid = msgget(key, IPC_CREAT | 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    struct message msg;
    msg.msg_type = 1; // Message type must be positive

    // Producer: send message
    strcpy(msg.msg_text, "Hello, message queue!");
    if (msgsnd(msgid, (void *)&msg, sizeof(msg.msg_text), IPC_NOWAIT) == -1) {
        perror("msgsnd");
        exit(EXIT_FAILURE);
    }
    printf("Producer: Data sent to message queue: %s\n", msg.msg_text);

    // Consumer: receive message
    if (msgrcv(msgid, (void *)&msg, sizeof(msg.msg_text), 1, 0) == -1) {
        perror("msgrcv");
        exit(EXIT_FAILURE);
    }
    printf("Consumer: Data received from message queue: %s\n", msg.msg_text);

    // Remove the message queue
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}

