/*
 ============================================================================
   C Program to Demonstrate UNIX System Calls for File Management
   System Calls Used: open(), write(), read(), lseek(), close()
 ============================================================================
*/

#include <stdio.h>
#include <fcntl.h>      // for open() and O_* constants
#include <unistd.h>     // for read(), write(), close(), lseek()
#include <string.h>     // for strlen()

int main() {
    int fd;  
    char buffer[100];
    ssize_t bytesRead;

    // 1. Create or open a file using open()
    fd = open("demo.txt", O_CREAT | O_RDWR, 0644);
    if (fd < 0) {
        perror("Error opening file");
        return 1;
    }
    printf("File opened successfully with fd = %d\n", fd);

    // 2. Write data into the file
    char text[] = "Hello, this is a test file using UNIX system calls.\n";
    if (write(fd, text, strlen(text)) < 0) {
        perror("Error writing to file");
        return 1;
    }
    printf("Data written to file successfully.\n");

    // 3. Move the file offset to the beginning
    lseek(fd, 0, SEEK_SET);

    // 4. Read the data back
    bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    if (bytesRead < 0) {
        perror("Error reading file");
        return 1;
    }
    buffer[bytesRead] = '\0';  // Null-terminate string
    printf("Data read from file: \n%s\n", buffer);

    // 5. Close the file
    if (close(fd) < 0) {
        perror("Error closing file");
        return 1;
    }
    printf("File closed successfully.\n");

    return 0;
}

