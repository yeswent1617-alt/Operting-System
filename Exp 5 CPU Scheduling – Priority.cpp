#include <stdio.h>

int main() {
    int n, i, j, total_wt = 0, total_tat = 0;
    int bt[20], p[20], wt[20], tat[20], priority[20], temp;
    float avg_wt, avg_tat;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input Burst Time and Priority
    for (i = 0; i < n; i++) {
        printf("Enter Burst Time for P%d: ", i + 1);
        scanf("%d", &bt[i]);
        printf("Enter Priority for P%d (higher number = higher priority): ", i + 1);
        scanf("%d", &priority[i]);
        p[i] = i + 1; // process ID
    }

    // Sort processes by priority (higher priority first)
    for (i = 0; i < n; i++) {
        for (j = i + 1; j < n; j++) {
            if (priority[j] > priority[i]) { // non-preemptive: higher priority first
                // Swap priority
                temp = priority[i];
                priority[i] = priority[j];
                priority[j] = temp;

                // Swap burst time
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;

                // Swap process ID
                temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    // Calculate Waiting Time
    wt[0] = 0;
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
        total_wt += wt[i];
    }

    // Calculate Turnaround Time
    printf("\nProcess\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_tat += tat[i];
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i], bt[i], priority[i], wt[i], tat[i]);
    }

    avg_wt = (float)total_wt / n;
    avg_tat = (float)total_tat / n;

    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}

