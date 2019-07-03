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
    newOne->Type = (enum Process_Type) READY;
    newOne->state = (enum Process_Status) CPU_BOUND;
    newOne->arrivalTime = -1;
    newOne->maxCPUTime = 0.0;// total CPU burst time
    newOne->maxIOTime = 0.0;
    newOne->waitTime = 0.0;
    newOne->blockTime = 0.0;
    newOne->numCPU = -1;
    newOne->estCPUBurst = NULL;
    newOne->cpuBurstTime = NULL;
    newOne->ioBurstTime = NULL;
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
void estimateTime(struct Process* newOne, double ALPHA) {
    for (int i = 0; i < newOne->numCPU - 1; i++) {
        newOne->estCPUBurst[i + 1] = ALPHA * newOne->cpuBurstTime[i] +
                                    (1 - ALPHA) * newOne->estCPUBurst[i];

    }
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
    if (left.maxCPUTime < right.maxCPUTime) return -1;
    if (left.maxCPUTime == right.maxCPUTime) return 0;
    if (left.maxCPUTime > right.maxCPUTime) return 1;
}