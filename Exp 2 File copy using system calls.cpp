#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *fptr1, *fptr2;
    char filename[100];
    int c;   // use int for fgetc() to handle EOF properly

    printf("Enter the filename to open for reading: ");
    scanf("%s", filename);

    fptr1 = fopen(filename, "r");
    if (fptr1 == NULL) {
        printf("Cannot open file %s\n", filename);
        exit(0);
    }

    printf("Enter the filename to open for writing: ");
    scanf("%s", filename);

    fptr2 = fopen(filename, "w");
    if (fptr2 == NULL) {
        printf("Cannot open file %s\n", filename);
        fclose(fptr1);
        exit(0);
    }

    // Copy contents character by character
    while ((c = fgetc(fptr1)) != EOF) {
        fputc(c, fptr2);
    }

    printf("\nContents copied successfully to %s\n", filename);

    fclose(fptr1);
    fclose(fptr2);
    return 0;
}

