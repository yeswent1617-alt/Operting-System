#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, i;
    int *arr;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // 1. malloc() - allocate memory
    arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("Memory allocation failed using malloc.\n");
        return 1;
    }

    printf("Memory allocated using malloc. Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    printf("Elements using malloc: ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 2. calloc() - allocate and initialize memory
    int *arr2 = (int *)calloc(n, sizeof(int));
    if (arr2 == NULL) {
        printf("Memory allocation failed using calloc.\n");
        free(arr);
        return 1;
    }

    printf("Memory allocated using calloc (initialized to 0): ");
    for (i = 0; i < n; i++) {
        printf("%d ", arr2[i]);
    }
    printf("\n");

    // 3. realloc() - resize memory
    int new_size;
    printf("Enter new size for realloc: ");
    scanf("%d", &new_size);

    arr = (int *)realloc(arr, new_size * sizeof(int));
    if (arr == NULL) {
        printf("Memory reallocation failed.\n");
        free(arr2);
        return 1;
    }

    // If new size is bigger, initialize new elements
    if (new_size > n) {
        for (i = n; i < new_size; i++) {
            arr[i] = i * 10; // example values
        }
    }

    printf("Elements after realloc: ");
    for (i = 0; i < new_size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    // 4. Free memory
    free(arr);
    free(arr2);

    printf("Memory deallocated successfully.\n");

    return 0;
}

