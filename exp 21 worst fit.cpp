/* 
 ============================================================================
    C Program to Implement Worst Fit Memory Allocation Algorithm
 ============================================================================
*/

#include <stdio.h>

void worstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n]; // Stores block index allocated to process

    // Initially no process is allocated
    for (int i = 0; i < n; i++)
        allocation[i] = -1;

    // Pick each process
    for (int i = 0; i < n; i++) {
        int worstIdx = -1;

        // Find the worst fit block for current process
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx])
                    worstIdx = j;
            }
        }

        // If we found a block
        if (worstIdx != -1) {
            // Allocate block j to process i
            allocation[i] = worstIdx;

            // Reduce available memory in this block
            blockSize[worstIdx] -= processSize[i];
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf(" %d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n;

    printf("Enter number of memory blocks: ");
    scanf("%d", &m);
    int blockSize[m];
    printf("Enter size of each block:\n");
    for (int i = 0; i < m; i++)
        scanf("%d", &blockSize[i]);

    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processSize[n];
    printf("Enter size of each process:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &processSize[i]);

    worstFit(blockSize, m, processSize, n);

    return 0;
}

