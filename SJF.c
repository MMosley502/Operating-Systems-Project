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
    printf("time %dms: Simulator started for SJF ", time);
    printQueue(readyQueue);// Empty Queue

    //================================================================
    // Sort the process by arrival time
    qsort(processListCopy, NUM_PROCESSES, sizeof(struct Process*), compareArrival);


    //================================================================
    // Implementation
    while (1) {
        //if all process done with their CPU bursts, break out of the loop
        if(allDone(processListCopy, NUM_PROCESSES)) {
            //break out of the loop and finishes SJF
            printf("time %dms: Simulator ended for SJF ", time);
            printQueue(readyQueue);
            break;
        }

        for (int i = 0; i < NUM_PROCESSES; i++) {
            // Constructing readyQueue
            // ProcessListCopy is an ascending array
            if (processListCopy[i]->state == NOT_ENTERED && time == processListCopy[i]->arrivalTime) {
                pushQueue(readyQueue, processListCopy[i]);
                sortQueue(readyQueue);
                printf("time %dms: Process %s (tau %0.0fms) arrived; added to ready queue ",
                       time, getProcessID(processListCopy[i]->ID), processListCopy[i]->nextEstBurst);
                printQueue(readyQueue);
                processListCopy[i]->nextInterest = time + CS_TIME / 2.0;// Entering CPU time
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
                popQueue(readyQueue);
                printf("time %dms: Process %s (tau %0.0fms) started using the CPU for %0.0fms burst ",
                       time, getProcessID(processListCopy[i]->ID), processListCopy[i]->nextEstBurst, burstTime);
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
                    processListCopy[i]->doneCPU++;
                    double ioTime = processListCopy[i]->ioBurstTime[idx];
                    int leftCPU = processListCopy[i]->numCPU - processListCopy[i]->doneCPU;// #of CPU left undone
                    double finiIO = processListCopy[i]->nextInterest + ioTime;// time when the process finishing IO
                    printf("time %dms: Process %s (tau %0.0fms) completed a CPU burst; %d bursts to go ",
                           time, getProcessID(processListCopy[i]->ID), processListCopy[i]->nextEstBurst, leftCPU);
                    printQueue(readyQueue);
                    double nextEstimate = estimateTime(processListCopy[i], ALPHA, idx);
                    processListCopy[i]->nextEstBurst = nextEstimate;
                    printf("time %dms: Recalculated tau = %0.0fms for process %s ", time, nextEstimate, getProcessID(processListCopy[i]->ID));
                    printQueue(readyQueue);
                    printf("time %dms: Process %s switching out of CPU; will block on I/O until time %0.0fms ",
                           time, getProcessID(processListCopy[i]->ID), finiIO);
                    printQueue(readyQueue);
                    //update status
                    processListCopy[i]->state = BLOCKED;
                    processListCopy[i]->nextInterest = time + ioTime;
                }
                CPU_Flag = false;// Release the CPU
            }

            // Finish I/O
            if (processListCopy[i]->state == BLOCKED && time == processListCopy[i]->nextInterest) {
                // After finished I/O, re-entering readyQueue
                pushQueue(readyQueue, processListCopy[i]);
                sortQueue(readyQueue);
                printf("time %dms: Process %s (tau %0.0fms) completed I/O; added to ready queue ",
                       time, getProcessID(processListCopy[i]->ID), processListCopy[i]->nextEstBurst);
                printQueue(readyQueue);

                processListCopy[i]->state = READY;
                processListCopy[i]->nextInterest = time + CS_TIME / 2.0;
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
    printAnalysis("SJF", processListCopy, NUM_PROCESSES, CSCounter, 0, CS_TIME);
    restore(processList, NUM_PROCESSES);
    free(readyQueue);
}