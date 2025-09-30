#include <stdio.h>

int main() {
    int n, tq, bt[20], at[20], rt[20], tat[20], wt[20], ct[20];
    int i, count = 0, time = 0, remain, flag;
    float avg_wt = 0, avg_tat = 0;

    printf("Total number of process in the system: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        printf("\nEnter the Arrival and Burst time of the Process[%d]\n", i + 1);
        printf("Arrival time is: ");
        scanf("%d", &at[i]);
        printf("Burst time is: ");
        scanf("%d", &bt[i]);
        rt[i] = bt[i];  // remaining time
    }

    printf("Enter the Time Quantum for the process: ");
    scanf("%d", &tq);

    remain = n;
    printf("\nProcess No\tBurst Time\tTAT\tWaiting Time\n");

    while (remain != 0) {
        flag = 0;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0 && at[i] <= time) {
                if (rt[i] <= tq) {
                    time += rt[i];
                    rt[i] = 0;
                    flag = 1;
                } else {
                    rt[i] -= tq;
                    time += tq;
                }

                if (rt[i] == 0 && flag == 1) {
                    remain--;
                    ct[i] = time;                // Completion Time
                    tat[i] = ct[i] - at[i];      // Turnaround Time
                    wt[i] = tat[i] - bt[i];      // Waiting Time
                    printf("Process No[%d]\t%d\t\t%d\t%d\n", i + 1, bt[i], tat[i], wt[i]);
                    avg_wt += wt[i];
                    avg_tat += tat[i];
                }
            }
        }
        // If no process has arrived yet, increase time
        int unfinished = 0;
        for (i = 0; i < n; i++) {
            if (rt[i] > 0) unfinished = 1;
        }
        if (unfinished && flag == 0) time++;
    }

    printf("\nAverage Turn Around Time: %.6f", avg_tat / n);
    printf("\nAverage Waiting Time: %.6f\n", avg_wt / n);

    return 0;
}

