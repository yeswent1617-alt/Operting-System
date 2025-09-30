#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SUBDIRS 10
#define MAX_FILES 100
#define NAME_LEN 50

typedef struct {
    char name[NAME_LEN];
} File;

typedef struct {
    char name[NAME_LEN];
    File files[MAX_FILES];
    int file_count;
} SubDirectory;

SubDirectory root[MAX_SUBDIRS];
int subdir_count = 0;

// Create a subdirectory
void createSubDir() {
    if (subdir_count >= MAX_SUBDIRS) {
        printf("Maximum subdirectories reached.\n");
        return;
    }

    char dirname[NAME_LEN];
    printf("Enter subdirectory name: ");
    scanf("%s", dirname);

    // Check if subdirectory already exists
    for (int i = 0; i < subdir_count; i++) {
        if (strcmp(root[i].name, dirname) == 0) {
            printf("Subdirectory already exists!\n");
            return;
        }
    }

    strcpy(root[subdir_count].name, dirname);
    root[subdir_count].file_count = 0;
    subdir_count++;
    printf("Subdirectory '%s' created successfully.\n", dirname);
}

// Create a file inside a subdirectory
void createFile() {
    if (subdir_count == 0) {
        printf("No subdirectories exist. Create a subdirectory first.\n");
        return;
    }

    char dirname[NAME_LEN];
    printf("Enter subdirectory name to create file in: ");
    scanf("%s", dirname);

    int found = -1;
    for (int i = 0; i < subdir_count; i++) {
        if (strcmp(root[i].name, dirname) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Subdirectory not found!\n");
        return;
    }

    if (root[found].file_count >= MAX_FILES) {
        printf("Maximum files reached in this subdirectory.\n");
        return;
    }

    char filename[NAME_LEN];
    printf("Enter file name to create: ");
    scanf("%s", filename);

    // Check if file already exists
    for (int j = 0; j < root[found].file_count; j++) {
        if (strcmp(root[found].files[j].name, filename) == 0) {
            printf("File already exists in this subdirectory!\n");
            return;
        }
    }

    strcpy(root[found].files[root[found].file_count].name, filename);
    root[found].file_count++;
    printf("File '%s' created in subdirectory '%s'.\n", filename, dirname);
}

// Display all subdirectories and files
void displayDirectory() {
    if (subdir_count == 0) {
        printf("No subdirectories exist.\n");
        return;
    }

    printf("Root Directory:\n");
    for (int i = 0; i < subdir_count; i++) {
        printf("  Subdirectory: %s\n", root[i].name);
        if (root[i].file_count == 0) {
            printf("    (No files)\n");
        } else {
            for (int j = 0; j < root[i].file_count; j++) {
                printf("    File: %s\n", root[i].files[j].name);
            }
        }
    }
}

// Search for a file
void searchFile() {
    if (subdir_count == 0) {
        printf("No subdirectories exist.\n");
        return;
    }

    char filename[NAME_LEN];
    printf("Enter file name to search: ");
    scanf("%s", filename);

    for (int i = 0; i < subdir_count; i++) {
        for (int j = 0; j < root[i].file_count; j++) {
            if (strcmp(root[i].files[j].name, filename) == 0) {
                printf("File '%s' found in subdirectory '%s'.\n", filename, root[i].name);
                return;
            }
        }
    }

    printf("File '%s' not found.\n", filename);
}

// Delete a file
void deleteFile() {
    if (subdir_count == 0) {
        printf("No subdirectories exist.\n");
        return;
    }

    char dirname[NAME_LEN];
    printf("Enter subdirectory name to delete file from: ");
    scanf("%s", dirname);

    int found = -1;
    for (int i = 0; i < subdir_count; i++) {
        if (strcmp(root[i].name, dirname) == 0) {
            found = i;
            break;
        }
    }

    if (found == -1) {
        printf("Subdirectory not found!\n");
        return;
    }

    char filename[NAME_LEN];
    printf("Enter file name to delete: ");
    scanf("%s", filename);

    int file_found = 0;
    for (int j = 0; j < root[found].file_count; j++) {
        if (strcmp(root[found].files[j].name, filename) == 0) {
            file_found = 1;
            // Shift remaining files
            for (int k = j; k < root[found].file_count - 1; k++) {
                strcpy(root[found].files[k].name, root[found].files[k + 1].name);
            }
            root[found].file_count--;
            printf("File '%s' deleted from subdirectory '%s'.\n", filename, dirname);
            break;
        }
    }

    if (!file_found) {
        printf("File not found in subdirectory '%s'.\n", dirname);
    }
}

int main() {
    int choice;

    while (1) {
        printf("\nTwo-Level Directory Menu:\n");
        printf("1. Create Subdirectory\n");
        printf("2. Create File\n");
        printf("3. Delete File\n");
        printf("4. Search File\n");
        printf("5. Display Directory Structure\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createSubDir(); break;
            case 2: createFile(); break;
            case 3: deleteFile(); break;
            case 4: searchFile(); break;
            case 5: displayDirectory(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

