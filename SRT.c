// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#include "includes.h"

void SRT(struct Process *processList[], int NUM_PROCESSES, int CS_TIME, double ALPHA, FILE* f) {
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
    int preemptionCounter = 0;
    int CSCounter = 0;
    int currentRunningPos = -1;// Mark the current running process
    int releaseCPU = -1;
    bool CPU_Flag = false;// flag the status of CPU. false is available, true is occupied
    printf("time %dms: Simulator started for SRT ", time);
    fflush(stdout);
    printQueue(readyQueue);// Empty Queue


    //================================================================
    // Implementation
    while (1) {

        if (time == 460) {
            printf("time %d ms: time breakpoint\n", time);
        }

        // CPU burst
        // Make sure only the first one in the readyQueue can enter the CPU burst
        // Make sure the CPU is available
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (processListCopy[i]->state == READY && time >= processListCopy[i]->nextInterest
                && processListCopy[i]->ID == getFront(readyQueue)->ID && !CPU_Flag) {
                double waitTime = time - processListCopy[i]->readyStart - CS_TIME / 2.0;
                processListCopy[i]->waitTimer += waitTime;
                int idx = processListCopy[i]->doneCPU;
                double burstTime = processListCopy[i]->cpuBurstTime[idx];// get the actual running time
                processListCopy[i]->nextActualBurst = burstTime;
                processListCopy[i]->inCS = false;
                popQueue(readyQueue);
                if (time <= 1999) {
                    printf("time %dms: Process %s (tau %0.0fms) started using the CPU with %0.0fms burst remaining ",
                           time, getProcessID(processListCopy[i]->ID), processListCopy[i]->oldEstBurst, burstTime);
                    fflush(stdout);
                    printQueue(readyQueue);
                }
                CPU_Flag = true;
                processListCopy[i]->state = RUNNING;
                processListCopy[i]->nextInterest = time + burstTime;
                processListCopy[i]->burstStart = time;
                currentRunningPos = i;
            }
        }


        // I/O
        // If CPU burst finished, estimating the next CPU burst time
        for (int i = 0; i < NUM_PROCESSES; i++) {
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
                    double finiIO = processListCopy[i]->nextInterest + ioTime +
                                    CS_TIME / 2.0;// time when the process finishing IO
                    if (time <= 1999) {
                        if (leftCPU == 1) {
                            printf("time %dms: Process %s (tau %0.0fms) completed a CPU burst; %d burst to go ",
                                   time, getProcessID(processListCopy[i]->ID), processListCopy[i]->oldEstBurst,
                                   leftCPU);
                            fflush(stdout);
                            printQueue(readyQueue);
                        } else {
                            printf("time %dms: Process %s (tau %0.0fms) completed a CPU burst; %d bursts to go ",
                                   time, getProcessID(processListCopy[i]->ID), processListCopy[i]->oldEstBurst,
                                   leftCPU);
                            fflush(stdout);
                            printQueue(readyQueue);
                        }
                    }
                    double nextEstimate = estimateTimeSRT(processListCopy[i], ALPHA, idx);
                    processListCopy[i]->nextEstBurst = ceil(nextEstimate);
                    processListCopy[i]->oldEstBurst = ceil(nextEstimate);
                    if (time <= 1999) {
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
                releaseCPU = time + CS_TIME / 2;
            }
        }


        // Finish I/O
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (processListCopy[i]->state == BLOCKED && time == processListCopy[i]->nextInterest) {
                // After finished I/O, re-entering readyQueue
                pushQueue(readyQueue, processListCopy[i]);
                sortQueue(readyQueue);
                if (!isPreemptive(currentRunningPos, processListCopy, readyQueue, time)) {
                    if (time <= 1999) {
                        printf("time %dms: Process %s (tau %0.0fms) completed I/O; added to ready queue ",
                               time, getProcessID(processListCopy[i]->ID), processListCopy[i]->nextEstBurst);
                        fflush(stdout);
                        printQueue(readyQueue);
                    }
                }
                processListCopy[i]->state = READY;
                processListCopy[i]->finishIO = time;
                if (CPU_Flag == true || (!isEmpty(readyQueue) && processListCopy[i] != getFront(readyQueue))) {
                    processListCopy[i]->nextInterest = time + CS_TIME;
                } else {
                    processListCopy[i]->nextInterest = time + CS_TIME / 2.0;
                }
                CSCounter++;
            }
        }

        ////////////////////Preemption Check///////////////////////
        if (isPreemptive(currentRunningPos, processListCopy, readyQueue,
                         time)) {// Need to preempt the current running process
            double remainingTime = processListCopy[currentRunningPos]->nextActualBurst -
                                   (time - processListCopy[currentRunningPos]->burstStart);
            if (remainingTime < processListCopy[currentRunningPos]->nextActualBurst || time == getFront(readyQueue)->finishIO) { //preempt during burst
                if (time <= 1999) {
                    printf("time %dms: Process %s (tau %0.0fms) completed I/O; preempting %s ",
                           time, getProcessID(getFront(readyQueue)->ID), getFront(readyQueue)->nextEstBurst,
                           getProcessID(processListCopy[currentRunningPos]->ID));
                    fflush(stdout);
                    printQueue(readyQueue);
                }
            } else { // will preempt
                if (time <= 1999) {
                    printf("time %dms: Process %s (tau %0.0fms) will preempt %s ",
                           time, getProcessID(getFront(readyQueue)->ID), getFront(readyQueue)->oldEstBurst,
                           getProcessID(processListCopy[currentRunningPos]->ID));
                    fflush(stdout);
                    printQueue(readyQueue);
                }
            }

            // Update preemptive process state
            processListCopy[currentRunningPos]->state = PREEMPTIVE;// Change the status of current process
            processListCopy[currentRunningPos]->nextActualBurst = remainingTime;
            int idx = processListCopy[currentRunningPos]->doneCPU;
            processListCopy[currentRunningPos]->cpuBurstTime[idx] = remainingTime;
//            processListCopy[currentRunningPos]->oldEstBurst = processListCopy[currentRunningPos]->nextEstBurst;
            processListCopy[currentRunningPos]->nextEstBurst = remainingTime;
            processListCopy[currentRunningPos]->nextInterest = time + CS_TIME / 2.0;
            currentRunningPos = -1;// Avoid the same process will be preempted and added to readyQ twice

            //Update the first position of readyQ and preemptive process
            getFront(readyQueue)->nextInterest = time + CS_TIME / 2.0;
            preemptionCounter++;
            CSCounter++;
            releaseCPU = time + CS_TIME / 2;

        }
        ////////////////////Preemption Check///////////////////////

        if (!CPU_Flag && !isEmpty(readyQueue)) {
            getFront(readyQueue)->inCS = true;
        }


        if (CPU_Flag && releaseCPU == time) {
            ////////////////
//            printf("time %dms: CPU release\n", time);
            ////////////////
            CPU_Flag = false;// Release the CPU
            if (!isEmpty(readyQueue)) {
                getFront(readyQueue)->nextInterest = time + CS_TIME / 2.0;
                getFront(readyQueue)->inCS = true;
                releaseCPU = -1;
            }

            for (int i = 0; i < NUM_PROCESSES; i++) {
                if (processListCopy[i]->state == PREEMPTIVE) {
                    ////////////////
//                    printf("time %dms: Preemptive process added into readyQueue\n", time);
                    ////////////////
                    processListCopy[i]->state = READY;
                    pushQueue(readyQueue, processListCopy[i]);
                    sortQueue(readyQueue);// Current running process will be at first
                }
            }
        }


        // Constructing readyQueue
        // ProcessListCopy is an ascending array
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (processListCopy[i]->state == NOT_ENTERED && time == processListCopy[i]->arrivalTime) {
                pushQueue(readyQueue, processListCopy[i]);
                sortQueue(readyQueue);
                if (time < 1999) {
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
                processListCopy[i]->readyStart = time;
                CSCounter++;
            }
        }


        // Termination
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (processListCopy[i]->state == TERMINATED && time == processListCopy[i]->nextInterest) {
                printf("time %dms: Process %s terminated ",
                       time, getProcessID(processListCopy[i]->ID));
                fflush(stdout);
                printQueue(readyQueue);
                processListCopy[i]->end = time;
            }
        }


        //if all process done with their CPU bursts, break out of the loop
        if (allDone(processListCopy, NUM_PROCESSES)) {
            //break out of the loop and finishes SJF
            time += CS_TIME / 2;//process removal time
            printf("time %dms: Simulator ended for SRT ", time);
            fflush(stdout);
            printQueue(readyQueue);
            break;
        }
        time++;
    }
    printAnalysis("SRT", processListCopy, NUM_PROCESSES, CSCounter, preemptionCounter, CS_TIME, f);
    restore(processList, NUM_PROCESSES);
    freeQueue(readyQueue);
}

