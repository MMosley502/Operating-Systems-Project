// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#include "includes.h"


/*
 * @Arg: None
 * Initializing a Process structure
 * @Return: A pointer to struct Process
 * Need to free memory
 */
struct Process* initilizer_Process() {
    struct Process* newOne = calloc(1, sizeof(struct Process));

    newOne->ID = -1;
    newOne->state = NOT_ENTERED;
    newOne->arrivalTime = -1;
    newOne->numCPU = 0;// number of CPU bursts
    newOne->doneCPU = 0;// number of CPU bursts done executing
    newOne->nextInterest = 0.0;//time point for next interesting event
    newOne->estCPUBurst = NULL;
    newOne->waitTime = 0.0;// wait time counter
    newOne->blockTime = 0.0;// block time counter
    newOne->cpuBurstTime = NULL;// Actual CPU burst time
    newOne->ioBurstTime = NULL;//Actual I/O burst time

}

/*
 * @Arg: The pointer points the array storing Burst Time in a struct
 * @Arg: The number of CPU bursts
 * @Arg: The upper bound
 * @Arg: Lambda constant
 * Calculating the CPU or IO burst time based on the random number
 * @Return: The total burst time(Sum of each part)
 */
double randomTime(double* Time, int numCPU, int MAX, double LAMBDA) {
    double r = 0.0, x = 0.0, counter = 0.0;
    for (int j = 0; j < numCPU; j++) {
        r = drand48();// uniform dist [0.00,1.00)
        x = -log(r) / LAMBDA;
        if (x > MAX) {/* avoid values that are far down the "long tail" of the distribution */
            j--;
            continue;
        }
        counter += x;
        Time[j] = floor(x);
    }
    return counter;
}
/*
 * Function for estimate the CPU burst time by alpha
 * For SJF & SRT
 */
double estimateTime(struct Process* newOne, double ALPHA, int pos) {
    // Current estimate time and actual time to calculate the next estimate time
    double result = ALPHA * newOne->cpuBurstTime[pos] +
                    (1 - ALPHA) * newOne->estCPUBurst[pos];
    return result;

}

/*
 * Function for transforming the sorted array to readyQueue
 */
void arrayToQueue(struct Process* processListCopy[], int NUM_PROCESSES, struct Queue* readyQueue) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        pushQueue(readyQueue, processListCopy[i]);
    }
}

/*
 * Function to indicate all the process done with their bursts
 */
bool allDone(struct Process* processList[], int NUM_PROCESSES){
    for(int i=0;i<NUM_PROCESSES;i++){
        if(processList[i]->doneCPU!=processList[i]->numCPU ||
        processList[i]->state!=TERMINATED) return false;
    }
    return true;
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

/*
 * Check any process arrives at the same time
 * If arrives at the same time, comparing the estburst time
 */
bool isArrivalSame(struct Process* checkProcess, struct Process* processListCopy[], int NUM_PROCESSES) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (processListCopy[i] != checkProcess && checkProcess->arrivalTime == processListCopy[i]->arrivalTime) {
            return true;
        }
    }
}

/*
 * @Return: the index of shortest estBurst time job with the arrival time
 */
int whichFirst(struct Process* checkProcess, struct Process* processListCopy[], int NUM_PROCESSES) {
    int result = -1;
    struct Process* flag = checkProcess;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (processListCopy[i] != flag && flag->arrivalTime == processListCopy[i]->arrivalTime) {
            if (processListCopy[i]->estCPUBurst[0] < flag->estCPUBurst[0]) {
                result = i;// a shorter process
                flag = processListCopy[i];
            }
        }
    }
    return result;
}