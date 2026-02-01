/*
 * Shortest Job First (SJF) CPU Scheduling Algorithm
 * Non-preemptive version
 */

#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

typedef struct {
    int pid;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int start_time;
} Process;

void printLine(int length) {
    for(int i = 0; i < length; i++) {
        printf("-");
    }
    printf("\n");
}

void printHeader() {
    printf("\n");
    for(int i = 0; i < 80; i++) printf("=");
    printf("\nSHORTEST JOB FIRST (SJF) SCHEDULING ALGORITHM\n");
    for(int i = 0; i < 80; i++) printf("=");
    printf("\n");
}

void displayInput(Process processes[], int n) {
    printf("\nInput Processes:\n");
    printLine(60);
    printf("%-10s %-15s %-15s\n", "Process", "Arrival Time", "Burst Time");
    printLine(60);
    
    for(int i = 0; i < n; i++) {
        printf("P%-9d %-15d %-15d\n", 
               processes[i].pid, 
               processes[i].arrival_time, 
               processes[i].burst_time);
    }
    printLine(60);
}

void sjfScheduling(Process processes[], int n) {
    int current_time = 0;
    int completed = 0;
    bool is_completed[n];
    
    // Initialize completion status
    for(int i = 0; i < n; i++) {
        is_completed[i] = false;
    }
    
    printHeader();
    displayInput(processes, n);
    
    // SJF scheduling logic
    while(completed != n) {
        int min_burst = INT_MAX;
        int shortest = -1;
        
        // Find process with minimum burst time among arrived processes
        for(int i = 0; i < n; i++) {
            if(processes[i].arrival_time <= current_time && 
               !is_completed[i] && 
               processes[i].burst_time < min_burst) {
                min_burst = processes[i].burst_time;
                shortest = i;
            }
        }
        
        if(shortest == -1) {
            // No process has arrived, increment time
            current_time++;
        } else {
            // Execute the shortest job
            processes[shortest].start_time = current_time;
            current_time += processes[shortest].burst_time;
            processes[shortest].completion_time = current_time;
            processes[shortest].turnaround_time = 
                processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = 
                processes[shortest].turnaround_time - processes[shortest].burst_time;
            
            is_completed[shortest] = true;
            completed++;
        }
    }
}

void displayResults(Process processes[], int n) {
    printf("\n");
    for(int i = 0; i < 80; i++) printf("=");
    printf("\nSCHEDULING RESULTS\n");
    for(int i = 0; i < 80; i++) printf("=");
    printf("\n\n");
    
    printf("%-10s %-10s %-10s %-10s %-12s %-10s %-10s\n",
           "Process", "Arrival", "Burst", "Start", "Complete", "TAT", "WT");
    printLine(80);
    
    float total_tat = 0;
    float total_wt = 0;
    
    for(int i = 0; i < n; i++) {
        total_tat += processes[i].turnaround_time;
        total_wt += processes[i].waiting_time;
        
        printf("P%-9d %-10d %-10d %-10d %-12d %-10d %-10d\n",
               processes[i].pid,
               processes[i].arrival_time,
               processes[i].burst_time,
               processes[i].start_time,
               processes[i].completion_time,
               processes[i].turnaround_time,
               processes[i].waiting_time);
    }
    
    printLine(80);
    
    float avg_tat = total_tat / n;
    float avg_wt = total_wt / n;
    
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);
    
    printf("\n");
    for(int i = 0; i < 80; i++) printf("=");
    printf("\n");
}

void displayGanttChart(Process processes[], int n) {
    printf("\nGANTT CHART:\n");
    printLine(80);
    
    // Sort processes by start time for Gantt chart (bubble sort)
    Process sorted[n];
    for(int i = 0; i < n; i++) {
        sorted[i] = processes[i];
    }
    
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(sorted[j].start_time > sorted[j + 1].start_time) {
                Process temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    
    // Print process names
    printf("|");
    for(int i = 0; i < n; i++) {
        printf(" P%d |", sorted[i].pid);
    }
    printf("\n");
    
    // Print timeline
    printf("0");
    for(int i = 0; i < n; i++) {
        printf("    %d", sorted[i].completion_time);
    }
    printf("\n");
    
    for(int i = 0; i < 80; i++) printf("=");
    printf("\n\n");
}

void runExample1() {
    printf("\n");
    for(int i = 0; i < 80; i++) printf("#");
    printf("\n# EXAMPLE 1\n");
    for(int i = 0; i < 80; i++) printf("#");
    printf("\n");
    
    Process processes[] = {
        {1, 0, 6, 0, 0, 0, 0},
        {2, 1, 8, 0, 0, 0, 0},
        {3, 2, 7, 0, 0, 0, 0},
        {4, 3, 3, 0, 0, 0, 0}
    };
    
    int n = sizeof(processes) / sizeof(processes[0]);
    
    sjfScheduling(processes, n);
    displayResults(processes, n);
    displayGanttChart(processes, n);
}

void runExample2() {
    printf("\n");
    for(int i = 0; i < 80; i++) printf("#");
    printf("\n# EXAMPLE 2\n");
    for(int i = 0; i < 80; i++) printf("#");
    printf("\n");
    
    Process processes[] = {
        {1, 0, 5, 0, 0, 0, 0},
        {2, 1, 3, 0, 0, 0, 0},
        {3, 2, 8, 0, 0, 0, 0},
        {4, 3, 6, 0, 0, 0, 0},
        {5, 4, 2, 0, 0, 0, 0}
    };
    
    int n = sizeof(processes) / sizeof(processes[0]);
    
    sjfScheduling(processes, n);
    displayResults(processes, n);
    displayGanttChart(processes, n);
}

int main() {
    runExample1();
    runExample2();
    
    return 0;
}
