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
    outEachProcess(processList, NUM_PROCESSES);
    //================================================================
    struct Process* processListCopy[NUM_PROCESSES];// Copy the process array, avoid any change to processlist
    memcpy(processListCopy, processList, sizeof(processListCopy));
    struct Queue* readyQueue = initizlizeQueue(MAXPROCESS);
    struct Queue* waitQueue = initizlizeQueue(MAXPROCESS);
    struct Queue* terminatedQueue = initizlizeQueue(MAXPROCESS);
    int terminatedProcess = 0;
    int burstCounter = 0;
    int time = 0;
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
            //restore the count of done CPU
            for(int i = 0;i < NUM_PROCESSES; i++){
                processListCopy[i]->doneCPU = 0;
            }
            //break out of the loop and finishes SJF
            printf("time %dms: Simulator ended for SJF ", time);
            printQueue(readyQueue);
            break;
        }

        for (int i = 0; i < NUM_PROCESSES; i++) {
            // Constructing readyQueue
            // ProcessListCopy is an ascending array
            // if arriving at the same time, comparing the estburst time
            // Assuming at most 2 processes arrive at the same time
            if (processListCopy[i]->state == NOT_ENTERED && time == processListCopy[i]->arrivalTime) {
                if (isArrivalSame(processListCopy[i], processListCopy, NUM_PROCESSES)) {// another process arrives at the same time
                    int index = whichFirst(processListCopy[i], processListCopy, NUM_PROCESSES);
                    if (index != -1) {
                        pushQueue(readyQueue, processListCopy[index]);
                        printf("time %dms: Process %s (tau %fms) arrived; added to ready queue ",
                               time,getProcessID(processListCopy[index]->ID), processListCopy[index]->estCPUBurst[0]);
                        printQueue(readyQueue);
                        processListCopy[index]->nextInterest += CS_TIME / 2;
                        processListCopy[index]->state = READY;
                    }
                }
                pushQueue(readyQueue, processListCopy[i]);
                printf("time %dms: Process %s (tau %fms) arrived; added to ready queue ",
                       time, getProcessID(processListCopy[i]->ID), processListCopy[i]->estCPUBurst[0]);
                printQueue(readyQueue);
                processListCopy[i]->nextInterest += CS_TIME / 2;
                processListCopy[i]->state = READY;
            }

            // CPU burst


            // I/O
            // If CPU burst finished, storing the actual burst time and estimating the next CPU burst time

            // Termination


        }


        time++;
    }
}

