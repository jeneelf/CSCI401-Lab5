// C program for implementation of Simulation 
#include<stdio.h> 
#include<limits.h>
#include<stdlib.h>
#include "process.h"
#include "util.h"
#include <stdbool.h>


// Function to find the waiting time for all  
// processes
void findWaitingTimeRR(ProcessType plist[], int n, int quantum) {
    int rem_bt[n]; // Array to store remaining burst times
    for (int i = 0; i < n; i++) {
        rem_bt[i] = plist[i].bt;
    }

    int t = 0; // Current time

    while (1) {
        int done = 1; // Flag to check if all processes are done

        for (int i = 0; i < n; i++) {
            // If burst time is remaining for this process
            if (rem_bt[i] > 0) {
                done = 0; // At least one process is not done

                if (rem_bt[i] > quantum) {
                    // Process cannot complete in this quantum
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    // Process can complete in this quantum
                    t += rem_bt[i];
                    plist[i].wt = t - plist[i].bt; // Waiting time
                    rem_bt[i] = 0; // Process is finished
                }
            }
        }

        // If all processes are done, break the loop
        if (done == 1) {
            break;
        }
    }
}


// Function to find the waiting time for all  
// processes 
void findWaitingTimeSJF(ProcessType plist[], int n) {
    int remainingBurstTime[n];
    for (int j = 0; j < n; j++) {
        remainingBurstTime[j] = plist[j].bt;
    }

    int complete = 0, t = 0;
    int shortest = -1, min_remaining_time = INT_MAX, finish_time;
    bool check;

    while (complete < n) {
        min_remaining_time = INT_MAX;
        shortest = -1;
        check = false;

        for (int j = 0; j < n; j++) {
            if ((plist[j].art <= t) && (remainingBurstTime[j] > 0) && (remainingBurstTime[j] < min_remaining_time)) {
                min_remaining_time = remainingBurstTime[j];
                shortest = j;
                check = true;
            }
        }

        if (!check) {
            t++;
            continue;
        }

        remainingBurstTime[shortest]--;
        t++;

        if (remainingBurstTime[shortest] == 0) {
            complete++;
            finish_time = t;
            plist[shortest].wt = finish_time - plist[shortest].bt - plist[shortest].art;
            if (plist[shortest].wt < 0) {
                plist[shortest].wt = 0;
            }
        }
    }
}



// Function to find the waiting time for all  
// processes 
void findWaitingTime(ProcessType plist[], int n)
{ 
    // waiting time for first process is 0, or the arrival time if not 
    plist[0].wt = 0 +  plist[0].art; 
  
    // calculating waiting time 
    for (int  i = 1; i < n ; i++ ) 
        plist[i].wt =  plist[i-1].bt + plist[i-1].wt; 
} 
  
// Function to calculate turn around time 
void findTurnAroundTime( ProcessType plist[], int n)
{ 
    // calculating turnaround time by adding bt[i] + wt[i] 
    for (int  i = 0; i < n ; i++) 
        plist[i].tat = plist[i].bt + plist[i].wt; 
} 
  
// Function to sort the Process acc. to priority
int my_comparer(const void *this, const void *that) {
    ProcessType *p1 = (ProcessType *)this;
    ProcessType *p2 = (ProcessType *)that;
    return p1->pri - p2->pri;  // Lower priority value means higher priority
}

//Function to calculate average time 
void findavgTimeFCFS( ProcessType plist[], int n) 
{ 
    //Function to find waiting time of all processes 
    findWaitingTime(plist, n); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nFCFS\n");
}

//Function to calculate average time 
void findavgTimeSJF( ProcessType plist[], int n) 
{ 
    //Function to find waiting time of all processes 
    findWaitingTimeSJF(plist, n); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nSJF\n");
}

//Function to calculate average time 
void findavgTimeRR( ProcessType plist[], int n, int quantum) 
{ 
    //Function to find waiting time of all processes 
    findWaitingTimeRR(plist, n, quantum); 
  
    //Function to find turn around time for all processes 
    findTurnAroundTime(plist, n); 
  
    //Display processes along with all details 
    printf("\n*********\nRR Quantum = %d\n", quantum);
}

//Function to calculate average time 
void findavgTimePriority( ProcessType plist[], int n) 
{ 
    int total_wt = 0, total_tat = 0;
    float awt, att;

    qsort(plist, n, sizeof(ProcessType), my_comparer);
    findWaitingTime(plist, n);
    findTurnAroundTime(plist, n);

    //Display processes along with all details 
    printf("\n*********\nPriority\n");

    printf("PID\tBT\tPR\tWT\tTAT\n");
    for (int i= 0; i < n; i++){
      printf("\t%d\t\t%d\t\t%d\t\t%d\n", plist[i].pid, plist[i].bt, plist[i].wt, plist[i].tat); 
    }
    int total_wt = 0;
    int total_tat = 0;
    for (int i= 0; i < n; i++){
      total_wt += plist[i].wt;
      total_tat += plist[i].tat;
    }
    printf("\nAverage waiting time = %.2f", awt); 
    printf("\nAverage turn around time = %.2f\n", att); 
} 

void printMetrics(ProcessType plist[], int n)
{
    int total_wt = 0, total_tat = 0; 
    float awt, att;
    
    printf("\tProcesses\tBurst time\tWaiting time\tTurn around time\n"); 
  
    // Calculate total waiting time and total turn  
    // around time 
    for (int  i=0; i<n; i++) 
    { 
        total_wt = total_wt + plist[i].wt; 
        total_tat = total_tat + plist[i].tat; 
        printf("\t%d\t\t%d\t\t%d\t\t%d\n", plist[i].pid, plist[i].bt, plist[i].wt, plist[i].tat); 
    } 
  
    awt = ((float)total_wt / (float)n);
    att = ((float)total_tat / (float)n);
    
    printf("\nAverage waiting time = %.2f", awt); 
    printf("\nAverage turn around time = %.2f\n", att); 
} 

ProcessType * initProc(char *filename, int *n) 
{
  	FILE *input_file = fopen(filename, "r");
	  if (!input_file) {
		    fprintf(stderr, "Error: Invalid filepath\n");
		    fflush(stdout);
		    exit(0);
	  }

    ProcessType *plist = parse_file(input_file, n);
  
    fclose(input_file);
  
    return plist;
}
  
// Driver code 
int main(int argc, char *argv[]) 
{ 
    int n; 
    int quantum = 2;

    ProcessType *proc_list;
  
    if (argc < 2) {
		   fprintf(stderr, "Usage: ./schedsim <input-file-path>\n");
		   fflush(stdout);
		   return 1;
	   }
    
  // FCFS
    n = 0;
    proc_list = initProc(argv[1], &n);
  
    findavgTimeFCFS(proc_list, n);
    
    printMetrics(proc_list, n);
  
  // SJF
    n = 0;
    proc_list = initProc(argv[1], &n);
   
    findavgTimeSJF(proc_list, n); 
   
    printMetrics(proc_list, n);
  
  // Priority
    n = 0; 
    proc_list = initProc(argv[1], &n);
    
    findavgTimePriority(proc_list, n); 
    
    printMetrics(proc_list, n);
    
  // RR
    n = 0;
    proc_list = initProc(argv[1], &n);
    
    findavgTimeRR(proc_list, n, quantum); 
    
    printMetrics(proc_list, n);
    
    return 0; 
} 