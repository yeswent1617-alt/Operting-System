#include <stdio.h>

#define P 10  // max number of processes
#define R 10  // max number of resources

int n, m; // n = processes, m = resources
int Allocation[P][R], Max[P][R], Need[P][R], Available[R];
int Finish[P], SafeSeq[P];

// Function to check if system is in safe state
int isSafe() {
    int Work[R];
    int count = 0;

    for (int i = 0; i < m; i++)
        Work[i] = Available[i];

    for (int i = 0; i < n; i++)
        Finish[i] = 0;

    while (count < n) {
        int found = 0;
        for (int p = 0; p < n; p++) {
            if (!Finish[p]) {
                int flag = 1;
                for (int j = 0; j < m; j++) {
                    if (Need[p][j] > Work[j]) {
                        flag = 0;
                        break;
                    }
                }

                if (flag) {
                    for (int j = 0; j < m; j++)
                        Work[j] += Allocation[p][j];

                    SafeSeq[count++] = p;
                    Finish[p] = 1;
                    found = 1;
                }
            }
        }
        if (!found) {
            return 0; // not safe
        }
    }
    return 1; // safe
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    printf("Enter Allocation Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("Enter Max Matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);

    printf("Enter Available Resources:\n");
    for (int j = 0; j < m; j++)
        scanf("%d", &Available[j]);

    // Calculate Need Matrix
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    if (isSafe()) {
        printf("\nSystem is in a SAFE STATE.\nSafe Sequence: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", SafeSeq[i]);
        printf("\n");
    } else {
        printf("\nSystem is in an UNSAFE STATE (Deadlock may occur).\n");
    }

    return 0;
}

