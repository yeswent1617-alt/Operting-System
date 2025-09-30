#include <stdio.h>

int main() {
    int A[100][4];   // [process_id, burst_time, waiting_time, turnaround_time]
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]);   // burst time
        A[i][0] = i + 1;         // process ID
    }

    // Sorting by burst time (Selection Sort)
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++) {
            if (A[j][1] < A[index][1])
                index = j;
        }
        // swap burst time
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;

        // swap process ID
        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }

    // Waiting time of first process = 0
    A[0][2] = 0;

    // Calculate waiting time for each process
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++) {
            A[i][2] += A[j][1];   // sum of burst times of all previous processes
        }
        total += A[i][2];
    }

    avg_wt = (float) total / n;  // average waiting time
    total = 0;

    printf("\nProcess  BurstTime  WaitingTime  TurnaroundTime\n");
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2];   // turnaround time = burst + waiting
        total += A[i][3];
        printf("P%d\t   %d\t      %d\t\t   %d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }

    avg_tat = (float) total / n;  // average turnaround time

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}

