#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_FILES 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
} File;

File directory[MAX_FILES];
int file_count = 0;

// Function to create a file
void createFile() {
    if (file_count >= MAX_FILES) {
        printf("Directory is full. Cannot create more files.\n");
        return;
    }

    char filename[NAME_LEN];
    printf("Enter file name to create: ");
    scanf("%s", filename);

    // Check if file already exists
    for (int i = 0; i < file_count; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            printf("File already exists!\n");
            return;
        }
    }

    strcpy(directory[file_count].name, filename);
    file_count++;
    printf("File '%s' created successfully.\n", filename);
}

// Function to delete a file
void deleteFile() {
    if (file_count == 0) {
        printf("Directory is empty.\n");
        return;
    }

    char filename[NAME_LEN];
    printf("Enter file name to delete: ");
    scanf("%s", filename);

    int found = 0;
    for (int i = 0; i < file_count; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            found = 1;
            // Shift remaining files
            for (int j = i; j < file_count - 1; j++) {
                strcpy(directory[j].name, directory[j + 1].name);
            }
            file_count--;
            printf("File '%s' deleted successfully.\n", filename);
            break;
        }
    }

    if (!found) {
        printf("File not found!\n");
    }
}

// Function to search for a file
void searchFile() {
    if (file_count == 0) {
        printf("Directory is empty.\n");
        return;
    }

    char filename[NAME_LEN];
    printf("Enter file name to search: ");
    scanf("%s", filename);

    for (int i = 0; i < file_count; i++) {
        if (strcmp(directory[i].name, filename) == 0) {
            printf("File '%s' found in directory.\n", filename);
            return;
        }
    }
    printf("File '%s' not found.\n", filename);
}

// Function to display all files
void displayFiles() {
    if (file_count == 0) {
        printf("Directory is empty.\n");
        return;
    }

    printf("Files in directory:\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s\n", directory[i].name);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nSingle-Level Directory Menu:\n");
        printf("1. Create File\n");
        printf("2. Delete File\n");
        printf("3. Search File\n");
        printf("4. Display All Files\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createFile(); break;
            case 2: deleteFile(); break;
            case 3: searchFile(); break;
            case 4: displayFiles(); break;
            case 5: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

