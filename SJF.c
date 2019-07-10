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
void SJF(struct Process *processList[], int NUM_PROCESSES, int CS_TIME, double ALPHA, FILE* f) {
    // Error check
    if (!processList || CS_TIME < 0 || ALPHA < 0) {
        return;
    }
    outEPS(processList, NUM_PROCESSES);
    //================================================================
    struct Process *processListCopy[NUM_PROCESSES];// Copy the process array, avoid any change to processlist
    memcpy(processListCopy, processList, sizeof(processListCopy));
    struct Queue *readyQueue = initizlizeQueue(MAXPROCESS);
    int time = 0;
    int CSCounter = 0;
    bool CPU_Flag = false;// flag the status of CPU. false is available, true is occupied
    printf("time %dms: Simulator started for SJF ", time);
    fflush(stdout);
    printQueue(readyQueue);// Empty Queue


    //================================================================
    // Implementation
    while (1) {

        for (int i = 0; i < NUM_PROCESSES; i++) {
            // Constructing readyQueue
            // ProcessListCopy is an ascending array
            if (processListCopy[i]->state == NOT_ENTERED && time == processListCopy[i]->arrivalTime) {
                pushQueue(readyQueue, processListCopy[i]);
                sortQueue(readyQueue);
                if (time <= 999) {
                    printf("time %dms: Process %s (tau %0.0fms) arrived; added to ready queue ",
                           time, getProcessID(processListCopy[i]->ID), processListCopy[i]->nextEstBurst);
                    fflush(stdout);
                    printQueue(readyQueue);
                }
                if (CPU_Flag == false) {
                    processListCopy[i]->nextInterest = time + CS_TIME / 2.0;
                } else {
                    processListCopy[i]->nextInterest = time + CS_TIME;
                }
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
                getFront(readyQueue)->inCS = false;
                popQueue(readyQueue);
                if (time <= 999) {
                    printf("time %dms: Process %s (tau %0.0fms) started using the CPU for %0.0fms burst ",
                           time, getProcessID(processListCopy[i]->ID), processListCopy[i]->nextEstBurst, burstTime);
                    fflush(stdout);
                    printQueue(readyQueue);
                }
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
                    double finiIO = processListCopy[i]->nextInterest + ioTime + CS_TIME / 2.0;// time when the process finishing IO
                    if (time <= 999) {
                        printf("time %dms: Process %s (tau %0.0fms) completed a CPU burst; %d bursts to go ",
                               time, getProcessID(processListCopy[i]->ID), processListCopy[i]->nextEstBurst, leftCPU);
                        fflush(stdout);
                        printQueue(readyQueue);
                        double nextEstimate = estimateTime(processListCopy[i], ALPHA, idx);
                        processListCopy[i]->nextEstBurst = ceil(nextEstimate);
                        printf("time %dms: Recalculated tau = %0.0fms for process %s ", time, ceil(nextEstimate),
                               getProcessID(processListCopy[i]->ID));
                        fflush(stdout);
                        printQueue(readyQueue);
                        printf("time %dms: Process %s switching out of CPU; will block on I/O until time %0.0fms ",
                               time, getProcessID(processListCopy[i]->ID), finiIO);
                        fflush(stdout);
                        printQueue(readyQueue);
                    }
                    //update status
                    processListCopy[i]->state = BLOCKED;
                    processListCopy[i]->nextInterest = time + ioTime + CS_TIME / 2.0;
                }
                CPU_Flag = false;// Release the CPU
                if (!isEmpty(readyQueue)) {
                    getFront(readyQueue)->nextInterest = time + CS_TIME;
                    getFront(readyQueue)->inCS = true;
                }
            }

            // Finish I/O
            if (processListCopy[i]->state == BLOCKED && time == processListCopy[i]->nextInterest) {
                // After finished I/O, re-entering readyQueue
                pushQueue(readyQueue, processListCopy[i]);
                sortQueue(readyQueue);
                if (time <= 999) {
                    printf("time %dms: Process %s (tau %0.0fms) completed I/O; added to ready queue ",
                           time, getProcessID(processListCopy[i]->ID), processListCopy[i]->nextEstBurst);
                    fflush(stdout);
                    printQueue(readyQueue);
                }
                processListCopy[i]->state = READY;
                if (CPU_Flag == true || (!isEmpty(readyQueue) && processListCopy[i] != getFront(readyQueue))) {
                    processListCopy[i]->nextInterest = time + CS_TIME;
                } else {
                    processListCopy[i]->nextInterest = time + CS_TIME / 2.0;
                }
                CSCounter++;
            }

            // Termination
            if (processListCopy[i]->state == TERMINATED && time == processListCopy[i]->nextInterest) {
                printf("time %dms: Process %s terminated ",
                       time, getProcessID(processListCopy[i]->ID));
                fflush(stdout);
                printQueue(readyQueue);
            }
        }
        //if all process done with their CPU bursts, break out of the loop
        if (allDone(processListCopy, NUM_PROCESSES)) {
            //break out of the loop and finishes SJF
            CSCounter++;//process removal time
            time += CS_TIME / 2;
            printf("time %dms: Simulator ended for SJF ", time);
            fflush(stdout);
            printQueue(readyQueue);
            break;
        }
        time++;
    }
    printAnalysis("SJF", processListCopy, NUM_PROCESSES, CSCounter, 0, CS_TIME, f);
    restore(processList, NUM_PROCESSES);
    freeQueue(readyQueue);
}
