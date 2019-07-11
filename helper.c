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
struct Process *initilizer_Process() {
    struct Process *newOne = calloc(1, sizeof(struct Process));

    newOne->ID = -1;
    newOne->state = NOT_ENTERED;
    newOne->arrivalTime = -1;
    newOne->numCPU = 0;// number of CPU bursts
    newOne->doneCPU = 0;// number of CPU bursts done executing
    newOne->nextInterest = 0.0;//time point for next interesting event
    newOne->initialEstBurst = 0.0;
    newOne->nextEstBurst = 0.0;
    newOne->nextActualBurst = 0.0;
    newOne->oldEstBurst = 0.0;
    newOne->burstStart = 0.0;
    newOne->waitTimer = 0.0;// wait time counter
    newOne->burstTimer = 0.0;
    newOne->numCS = 0;
    newOne->numPre = 0;
    newOne->sumWait = 0.0;
    newOne->preFlag = false;
    newOne->inCS = false;
    newOne->end = 0;
    newOne->maxIOTime = 0;

    return newOne;
}

double randomNumber(int MAX, double LAMBDA ){
    while(1){
        double r = drand48();// uniform dist [0.00,1.00)
        double x = -log(r) / LAMBDA;
        if (x > MAX) {/* avoid values that are far down the "long tail" of the distribution */
            continue;
        }
        else{
            return x;
        }
    }
}

/*
 * @Arg: The pointer points the array storing Burst Time in a struct
 * @Arg: The number of CPU bursts
 * @Arg: The upper bound
 * @Arg: Lambda constant
 * Calculating the CPU or IO burst time based on the random number
 * @Return: The total burst time(Sum of each part)
 */
double randomTime(double Time[], int numCPU, int MAX, double LAMBDA) {
    double r = 0.0, x = 0.0, counter = 0.0;
    for (int j = 0; j < numCPU; j++) {
        r = drand48();// uniform dist [0.00,1.00)
        x = -log(r) / LAMBDA;
        if (x > MAX) {/* avoid values that are far down the "long tail" of the distribution */
            j--;
            continue;
        }
        counter += floor(x);
        Time[j] = floor(x);
    }
    return counter;
}

///*
// * Function for estimate the CPU burst time by alpha
// * For SJF & SRT
// */
double estimateTime(struct Process *newOne, double ALPHA, int pos) {
    // Current estimate time and actual time to calculate the next estimate time
    double result = ALPHA * newOne->cpuBurstTime[pos] +
                    (1 - ALPHA) * newOne->nextEstBurst;
    return result;

}

double estimateTimeSRT(struct Process *newOne, double ALPHA, int pos) {
    // Current estimate time and actual time to calculate the next estimate time
    double result = ALPHA * newOne->cpuBurstTimeCopy[pos] +
                    (1 - ALPHA) * newOne->oldEstBurst;
    return result;

}


/*
 * Function to indicate all the process done with their bursts
 */
bool allDone(struct Process *processList[], int NUM_PROCESSES) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (processList[i]->doneCPU != processList[i]->numCPU ||
            processList[i]->state != TERMINATED)
            return false;
    }
    return true;
}

/*
 * Free the dynamic memeory of Process List
 */
void freeProcessList(struct Process *processList[], int NUM_PROCESSES) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if (processList[i]) {
            free(processList[i]);
        }
    }
}

/*
 * Function for comparing the current running process and the first process at the readyQueue
 * Deciding which one has the shorter burst time and has the priority to use CPU
 * Check whether any other process will complete I/O at the same time and has the shorter nextEstBurst
 * If yes, skip the current preemption.
 * @Return: True if will be preemptive
 */
bool isPreemptive(int currentRunningPos, struct Process *processListCopy[],
                  struct Queue *readyQueue, int time) {
    if (currentRunningPos == -1 || isEmpty(readyQueue)) {// No running process
        return false;
    }
    struct Process *current = processListCopy[currentRunningPos];
    struct Process *first = getFront(readyQueue); // current running process comparing with the first one in the readyQueue
    double remainingTime = current->nextEstBurst - (time - current->burstStart);
    if (remainingTime <= first->nextEstBurst) {
        return false;
    }
    return true;
}


/*
 * Restoring process, preparing for another algorithm
 */
void restore(struct Process *processList[], int NUM_PROCESSES) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        struct Process *curProcess = processList[i];
        curProcess->state = NOT_ENTERED;
        curProcess->nextInterest = 0;
        curProcess->doneCPU = 0;
        curProcess->waitTimer = 0;
        curProcess->burstTimer = 0;
        curProcess->sumWait = 0;
        curProcess->numCS = 0;
        curProcess->nextEstBurst = curProcess->initialEstBurst;
        for (int q = 0; q < 101; q++) {
            processList[i]->cpuBurstTime[q] = processList[i]->cpuBurstTimeCopy[q];
        }
    }
}
