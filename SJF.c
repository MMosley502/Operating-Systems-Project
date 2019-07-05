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
    outEPS(processList, NUM_PROCESSES);
    //================================================================
    struct Process* processListCopy[NUM_PROCESSES];// Copy the process array, avoid any change to processlist
    memcpy(processListCopy, processList, sizeof(processListCopy));
    struct Queue* readyQueue = initizlizeQueue(MAXPROCESS);
    int time = 0;
    int CSCounter = 0;
    bool CPU_Flag = false;// flag the status of CPU. false is available, true is occupied
    printf("time %dms: Simulator started for SJF", time);
    printQueue(readyQueue);// Empty Queue

    //================================================================
    // Sort the process by arrival time
    qsort(processListCopy, NUM_PROCESSES, sizeof(struct Process*), compareArrival);


    //================================================================
    // Implementation
    while (1) {
        //if all process done with their CPU bursts, break out of the loop
        if(allDone(processListCopy, NUM_PROCESSES)){
            //break out of the loop and finishes SJF
            printf("time %dms: Simulator ended for SJF ", time);
            printQueue(readyQueue);
            printAnalysis(processListCopy, NUM_PROCESSES, CSCounter, 0, CS_TIME);
            break;
        }

        for (int i = 0; i < NUM_PROCESSES; i++) {
            // Constructing readyQueue
            // ProcessListCopy is an ascending array
            if (processListCopy[i]->state == NOT_ENTERED && time == processListCopy[i]->arrivalTime) {
                pushQueue(readyQueue, processListCopy[i]);
                sortQueue(readyQueue);
                printf("time %dms: Process %s (tau %fms) arrived; added to ready queue ",
                       time, getProcessID(processListCopy[i]->ID), processListCopy[i]->estCPUBurst[0]);
                printQueue(readyQueue);
                processListCopy[i]->nextInterest = time + CS_TIME / 2;// Entering CPU time
                processListCopy[i]->state = READY;
                CSCounter++;
            }

            // CPU burst
            // Make sure only the first one in the readyQueue can enter the CPU burst
            // Make sure the CPU is available
            if (processListCopy[i]->state == READY && time >= processListCopy[i]->nextInterest
                && processListCopy[i]->ID == getFront(readyQueue)->ID && !CPU_Flag) {
                double waitTime = time - processListCopy[i]->nextInterest;
                int idx = processListCopy[i]->doneCPU;
                double burstTime = processListCopy[i]->cpuBurstTime[idx];
                printf("time %dms: Process %s (tau %fms) started using the CPU for %fms burst ",
                       time,getProcessID(processListCopy[i]->ID), processListCopy[i]->estCPUBurst[idx], burstTime);
                popQueue(readyQueue);
                printQueue(readyQueue);
                CPU_Flag = true;
                processListCopy[i]->state = RUNNING;
                processListCopy[i]->nextInterest = time + burstTime;
                processListCopy[i]->waitTimer += waitTime;
                processListCopy[i]->burstTimer += burstTime;
            }

            // I/O
            // If CPU burst finished, estimating the next CPU burst time
            if (processListCopy[i]->state == RUNNING && time == processListCopy[i]->nextInterest) {
                int idx = processListCopy[i]->doneCPU;
                // Check the status
                if (idx + 1 == processListCopy[i]->numCPU) {
                    processListCopy[i]->state = TERMINATED;
                    processListCopy[i]->doneCPU++;

                } else {
                    double ioTime = processListCopy[i]->ioBurstTime[idx];
                    int leftCPU = processListCopy[i]->numCPU - processListCopy[i]->doneCPU;// #of CPU left undone
                    double finiIO = processListCopy[i]->nextInterest + ioTime;// time when the process finishing IO
                    printf("time %dms: Process %s (tau %fms) completed a CPU burst; %d bursts to go ",
                           time, getProcessID(processListCopy[i]->ID), processListCopy[i]->estCPUBurst[idx], leftCPU);
                    printQueue(readyQueue);
                    double nextEstimate = estimateTime(processListCopy[i], ALPHA, idx);
                    processListCopy[i]->nextEstBurst = nextEstimate;
                    printf("time %dms: Recalculated tau = %fms for process %s ", time, nextEstimate, getProcessID(processListCopy[i]->ID));
                    printQueue(readyQueue);
                    printf("time %dms: Process %s switching out of CPU; will block on I/O until time %lfms ",
                           time, getProcessID(processListCopy[i]->ID), finiIO);
                    printQueue(readyQueue);
                    //update status
                    processListCopy[i]->state = BLOCKED;
                    processListCopy[i]->nextInterest = time + ioTime;
                    processListCopy[i]->doneCPU++;
                }
                CPU_Flag = false;// Release the CPU
            }

            // Finish I/O
            if (processListCopy[i]->state == BLOCKED && time == processListCopy[i]->nextInterest) {
                int idx = processListCopy[i]->doneCPU;
                // After finished I/O, re-entering readyQueue
                pushQueue(readyQueue, processListCopy[i]);
                sortQueue(readyQueue);
                printf("time %dms: Process %s (tau %fms) completed I/O; added to ready queue ",
                       time, getProcessID(processListCopy[i]->ID), processListCopy[i]->estCPUBurst[idx]);
                printQueue(readyQueue);

                processListCopy[i]->state = READY;
                processListCopy[i]->nextInterest = time + CS_TIME / 2;
                CSCounter++;
            }

            // Termination
            if (processListCopy[i]->state == TERMINATED && time == processListCopy[i]->nextInterest) {
                printf("time %dms: Process %s terminated ",
                       time, getProcessID(processListCopy[i]->ID));
                printQueue(readyQueue);
            }
        }
        time++;
    }

    free(readyQueue);
}

/*
 * Function for general printing of analysis
 * If any argument is not applied to a specific algo
 * Just give 0
 * add #include <fcntl.h>
 */
void printAnalysis(struct Process* processList[], int NUM_PROCESSES, int CSCounter, int preemptionCounter, int CS_TIME) {
    char* name = "simout.txt";
    int fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0660);
    if ( fd == -1 ) {
        perror( "open() failed" );
        return;
    }

//    -- average CPU burst time:  ms
//    -- average wait time:  ms
//    -- average turnaround time:  ms
//    -- total number of context switches:
//        -- total number of preemptions:
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
        sum += processList[i]->burstTimer;
    }
    return sum / NUM_PROCESSES;
}

double computeAveTurnAround(struct Process* processList[], int CSCounter, int NUM_PROCESSES, int CS_TIME) {
    double sum = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        sum += processList[i]->waitTimer;
        sum += processList[i]->burstTimer;
    }
    sum += (((double) CSCounter / 2) * CS_TIME);// Total turnaround time
    return sum / NUM_PROCESSES;
}
