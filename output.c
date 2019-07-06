// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#include "includes.h"

/*
 * Helper function for comparing the arriving time of each process
 * Apply to qsort() to sort array by arriving time
 * qsort(array, size of array, sizeof(struct process*), compareTime);
 * Reference: http://www.cplusplus.com/reference/cstdlib/qsort/
 */
int compareArrival(const void * a, const void * b) {
    struct Process left = *(struct Process*)a;
    struct Process right = *(struct Process*)b;
    if (left.arrivalTime < right.arrivalTime) return -1;
    if (left.arrivalTime == right.arrivalTime) return 0;
    if (left.arrivalTime > right.arrivalTime) return 1;
}

//output each process in the process list
// Print as the ascending order of process ID
void outEachProcess(struct Process* processList[], int NUM_PROCESSES) {
    for(int i = 0;i < NUM_PROCESSES; i++) {
        printf("Process %s [NEW] (arrival time %d ms) %d CPU bursts\n",
               getProcessID(processList[i]->ID), processList[i]->arrivalTime, processList[i]->numCPU);
    }
}

//output each process in the process list for SJF and SRT
// Print extra estimate time
// Print as the ascending order of process ID
void outEPS(struct Process* processList[], int NUM_PROCESSES) {
    for(int i = 0;i < NUM_PROCESSES; i++) {
        printf("Process %s [NEW] (arrival time %d ms) %d CPU bursts (tau %fms)\n",
               getProcessID(processList[i]->ID), processList[i]->arrivalTime, processList[i]->numCPU,
               processList[i]->estCPUBurst[0]);
    }
}

/*
 * Converting the Process ID from number to alpabetic
 */
char* getProcessID(int numberID) {
    char* Alphabetic[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q",
                            "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    return Alphabetic[numberID - 1];
}


/*
 * Function for general printing of analysis
 * If any argument is not applied to a specific algo
 * Just give 0
 */
void printAnalysis(char* algo, struct Process* processList[], int NUM_PROCESSES, int CSCounter,
                   int preemptionCounter, int CS_TIME) {
    double aveBurst = computeAveBurst(processList, NUM_PROCESSES);
    double aveWait = computeAveWait(processList, NUM_PROCESSES);
    double aveTurnAround = computeAveTurnAround(processList, CSCounter, NUM_PROCESSES, CS_TIME);
    printf("Algorithm %s\n", algo);
    printf("-- average CPU burst time: %lf ms\n", aveBurst);
    printf("-- average wait time: %lf ms\n", aveWait);
    printf("-- average turnaround time: %lf ms\n", aveTurnAround);
    printf("-- total number of context switches: %d\n", CSCounter);
    printf("-- total number of preemptions: %d\n", preemptionCounter);
}

double computeAveWait(struct Process* processList[], int NUM_PROCESSES) {
    double sum = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        sum += processList[i]->waitTimer;
    }
    return sum / NUM_PROCESSES;
}


double computeAveBurst(struct Process* processList[], int NUM_PROCESSES) {
    double sum = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        sum += processList[i]->maxCPUTime;
    }
    return sum / NUM_PROCESSES;
}

double computeAveTurnAround(struct Process* processList[], int CSCounter, int NUM_PROCESSES, int CS_TIME) {
    double sum = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        sum += processList[i]->waitTimer;
        sum += processList[i]->maxCPUTime;
    }
    sum += (CSCounter * (CS_TIME / 2));// Total turnaround time
    return sum / NUM_PROCESSES;
}
