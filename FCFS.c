// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)
#include "includes.h"

void FCFS(struct Process *processList[], int NUM_PROCESSES, int CS_TIME, FILE* f) {

    //output each process in the process list
    outEachProcess(processList, NUM_PROCESSES);

    //initializing ready queue
    struct Queue *readyQueue = initizlizeQueue(NUM_PROCESSES);

    //counter of system running time
    int time = 0;
    //false: cpu is vacant; true: cpu is not vacant
    bool cpuFlag = false;

    while (1) {

        //////////////////time zero//////////////////
        if (time == 0) {
            printf("time %dms: Simulator started for FCFS [Q <empty>]\n", time);
            fflush(stdout);
        }

        //////////////////running start//////////////////
        for (int i = 0; i < NUM_PROCESSES; i++) {

            /*-----------process is doing CPU burst-----------*/
            if (processList[i]->state == READY && time == processList[i]->nextInterest &&
                processList[i] == getFront(readyQueue) && cpuFlag == false) {
                //move the process out of the ready queue
                popQueue(readyQueue);
                //get the actual CPU burst time for the current process
                int idx = processList[i]->doneCPU;
                double burstTime = processList[i]->cpuBurstTime[idx];
                //output
                if (time <= 999) {
                    printf("time %dms: Process %s started using the CPU for %0.0fms burst ",
                           time, getProcessID(processList[i]->ID), burstTime);
                    fflush(stdout);
                    printQueue(readyQueue);
                }
                //when ready queue is not empty, update the next process interesting time
                if (!isEmpty(readyQueue)) {
                    struct Process *nextProcess = getFront(readyQueue);
                    nextProcess->nextInterest = time + burstTime + CS_TIME;
                }
                //update
                processList[i]->state = RUNNING;
                processList[i]->nextInterest = time + burstTime;
                processList[i]->numCS++;
                cpuFlag = true;
                //count wait time
                processList[i]->waitTimer += time - processList[i]->sumWait - CS_TIME / 2.0;
            }

        }


        for (int i = 0; i < NUM_PROCESSES; i++) {
            /*-----------process is finishing CPU burst-----------*/
            if (processList[i]->state == RUNNING && time == processList[i]->nextInterest) {
                //get the actual I/O burst time for the current process
                int idx = processList[i]->doneCPU;
                //process is terminating
                if (idx + 1 == processList[i]->numCPU) {
                    //updates
                    processList[i]->state = TERMINATED;
                    processList[i]->doneCPU++;
                    processList[i]->numCS++;
                    //count turnaround time
                    processList[i]->end = time;
                    //output
                    printf("time %dms: Process %s terminated ",
                           time, getProcessID(processList[i]->ID));
                    fflush(stdout);
                    printQueue(readyQueue);
                } else {
                    double ioTime = processList[i]->ioBurstTime[idx];
                    int leftCPU = processList[i]->numCPU - processList[i]->doneCPU - 1;// #of CPU left undone
                    processList[i]->nextInterest = time + CS_TIME / 2.0 + ioTime;// time when the process finishing IO
                    //output
                    if (time <= 999) {
                        if (leftCPU == 1) {
                            printf("time %dms: Process %s completed a CPU burst; %d burst to go ",
                                   time, getProcessID(processList[i]->ID), leftCPU);
                        } else {
                            printf("time %dms: Process %s completed a CPU burst; %d bursts to go ",
                                   time, getProcessID(processList[i]->ID), leftCPU);
                        }
                        fflush(stdout);
                        printQueue(readyQueue);
                        printf("time %dms: Process %s switching out of CPU; will block on I/O until time %0.0fms ",
                               time, getProcessID(processList[i]->ID), processList[i]->nextInterest);
                        fflush(stdout);
                        printQueue(readyQueue);
                    }
                    //update
                    processList[i]->state = BLOCKED;
                    processList[i]->nextInterest = time + CS_TIME / 2.0 + ioTime;
                    processList[i]->doneCPU++;
                    processList[i]->numCS++;
                }
                //when ready queue is not empty, update the next process interesting time
                if (!isEmpty(readyQueue)) {
                    struct Process *nextProcess = getFront(readyQueue);
                    nextProcess->nextInterest = time + CS_TIME;
                }
                cpuFlag = false;
            }
        }

        for (int i = 0; i < NUM_PROCESSES; i++) {
            /*-----------process is finishing I/O-----------*/
            if (processList[i]->state == BLOCKED && time == processList[i]->nextInterest) {
                //add the current process into ready queue
                pushQueue(readyQueue, processList[i]);
                //output
                if (time <= 999) {
                    printf("time %dms: Process %s completed I/O; added to ready queue ",
                           time, getProcessID(processList[i]->ID));
                    fflush(stdout);
                    printQueue(readyQueue);
                }
                //update
                //when cpu is occupied, current process next interesting time should plus previous process CS time
                if (cpuFlag == true || (!isEmpty(readyQueue) && processList[i] != getFront(readyQueue))) {
                    processList[i]->nextInterest = time + CS_TIME;
                } else {
                    processList[i]->nextInterest = time + CS_TIME / 2.0;
                }
                processList[i]->state = READY;
                processList[i]->sumWait = time;
            }

        }

        for (int i = 0; i < NUM_PROCESSES; i++) {
            /*-----------process is arriving-----------*/
            if (processList[i]->state == NOT_ENTERED && time == processList[i]->arrivalTime) {
                //add the arriving process into ready queue
                pushQueue(readyQueue, processList[i]);
                //updates
                //when cpu is occupied, current process next interesting time should plus previous process CS time
                if (cpuFlag == false) {
                    processList[i]->nextInterest = time + CS_TIME / 2.0;
                } else {
                    processList[i]->nextInterest = time + CS_TIME;
                }
                processList[i]->state = READY;
                //output
                if (time <= 999) {
                    printf("time %dms: Process %s arrived; added to ready queue ",
                           time, getProcessID(processList[i]->ID));
                    fflush(stdout);
                    printQueue(readyQueue);
                }
                processList[i]->sumWait = time;
            }
        }

        //////////////////algo terminating//////////////////
        //if all process done with their CPU bursts, break out of the loop
        if (allDone(processList, NUM_PROCESSES)) {
            time += CS_TIME / 2;
            printf("time %dms: Simulator ended for FCFS ", time);
            fflush(stdout);
            printQueue(readyQueue);
            break;
        }
        time++;

    }


    // Calculate the sum of CS times
    int CSCounter = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        CSCounter += processList[i]->numCS;
    }
    CSCounter=CSCounter/2;
    // No preemption in FCFS, just set as 0
    printAnalysis("FCFS", processList, NUM_PROCESSES, CSCounter, 0, CS_TIME, f);


    //restore
    restore(processList, NUM_PROCESSES);
    freeQueue(readyQueue);
}

