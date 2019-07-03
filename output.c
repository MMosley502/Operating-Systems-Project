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
int compareArrival(const void * a, const void * b){
    struct Process left = *(struct Process*)a;
    struct Process right = *(struct Process*)b;
    if (left.arrivalTime < right.arrivalTime) return -1;
    if (left.arrivalTime == right.arrivalTime) return 0;
    if (left.arrivalTime > right.arrivalTime) return 1;
}

//output each process in the process list
void outEachProcess(struct Process* processList[], int NUM_PROCESSES){
    //copy the original process list for sorting
    struct Process* processListCopy[NUM_PROCESSES];
    memcpy(processListCopy, processList, sizeof(processListCopy));
    //sort process by its arrival time
    qsort(processListCopy, NUM_PROCESSES, sizeof(struct process*), compareArrival);
    for(int i = 0;i < NUM_PROCESSES; i++){
        printf("Process %s [NEW] (arrival time %d ms) %d CPU bursts\n",
               getProcessID(processListCopy[i]->ID), processListCopy[i]->arrivalTime, processListCopy[i]->numCPU);
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