// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#include "includes.h"
/*
 * @Arg: The array includes all processes
 * @Arg: Context switch time
 * @Arg: Alpha constant
 * Implementing Shortest Job First Algorithm
 */
void SJF(struct Process* processList[], int NUM_PROCESSES, int CS_TIME, double ALPHA) {
    // Error check
    if (!processList || CS_TIME < 0 || ALPHA < 0) {
        return;
    }
    //================================================================
    struct Process* processListCopy[NUM_PROCESSES];
    memcpy(processListCopy, processList, sizeof(processListCopy));
    struct Queue* readyQueue = initizlizeQueue(MAXPROCESS);
    struct Process* blockList[MAXPROCESS];
    int terminatedProcess = 0;
    int totalTime = 0;
    printf("time %dms: Simulator started for SJF", totalTime);
    printQueue(readyQueue);// Empty Queue
    //================================================================
    // Sort the process and construct the readyQueue
    qsort(processListCopy, NUM_PROCESSES, sizeof(struct process*), compareTime);
    arrayToQueue(processListCopy, NUM_PROCESSES, readyQueue);
    //================================================================
}


/*
 * Helper function for comparing the length of CPU burst time of each process
 * Apply to qsort() to sort array by CPU burst time
 * qsort(array, size of array, sizeof(struct process*), compareTime);
 * Reference: http://www.cplusplus.com/reference/cstdlib/qsort/
 */
int compareTime(const void * a, const void * b) {
    struct Process left = *(struct Process*)a;
    struct Process right = *(struct Process*)b;
    if (left.estCPUBurst[0] < right.estCPUBurst[0]) return -1;
    if (left.estCPUBurst[0] == right.estCPUBurst[0]) return 0;
    if (left.estCPUBurst[0] > right.estCPUBurst[0]) return 1;
}
