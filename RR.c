// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#include "includes.h"

void RR(struct Process *processList[], int NUM_PROCESSES, int CS_TIME, double TIME_SLICE, char *RR_ADD, FILE* f) {

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
            printf("time %dms: Simulator started for RR [Q <empty>]\n", time);
            fflush(stdout);
        }


        //////////////////running start//////////////////
        for (int i = 0; i < NUM_PROCESSES; i++) {

            /*-----------process is arriving-----------*/
            if (processList[i]->state == NOT_ENTERED && time == processList[i]->arrivalTime) {
                //add the arriving process into ready queue
                pushQueue(readyQueue, processList[i]);
                //updates
                //when cpu is occupied, current process next interesting time should plus previous process CS time
                if (cpuFlag == false) {
                    processList[i]->nextInterest = time + CS_TIME / 2.0;
                    processList[i]->sumWait = time + CS_TIME / 2.0;
                } else {
                    processList[i]->nextInterest = time + CS_TIME;
                    processList[i]->sumWait = time + CS_TIME;
                }
                processList[i]->state = READY;
                //output
                if (time <= 999) {
                    printf("time %dms: Process %s arrived; added to ready queue ",
                           time, getProcessID(processList[i]->ID));
                    fflush(stdout);
                    printQueue(readyQueue);
                }
            }

            /*-----------process is doing CPU burst-----------*/
            if (processList[i]->state == READY && time == processList[i]->nextInterest &&
                processList[i] == getFront(readyQueue) && cpuFlag == false) {
                //move the process out of the ready queue
                popQueue(readyQueue);
                //get the actual CPU burst time for the current process
                int idx = processList[i]->doneCPU;
                double burstTime = processList[i]->cpuBurstTime[idx];
                //output
                //when the process is not preempted in the ready queue
                if (time <= 999) {
                    if (processList[i]->preFlag == false) {
                        printf("time %dms: Process %s started using the CPU for %0.0lfms burst ",
                               time, getProcessID(processList[i]->ID), burstTime);
                        fflush(stdout);
                    } else {
                        printf("time %dms: Process %s started using the CPU with %0.0lfms burst remaining ",
                               time, getProcessID(processList[i]->ID), burstTime);
                        fflush(stdout);
                    }
                    printQueue(readyQueue);
                }
                //update
                //preemption
                if (!isEmpty(readyQueue) && burstTime > TIME_SLICE) {
                    processList[i]->nextInterest = time + TIME_SLICE;
                    processList[i]->state = PREEMPTIVE;
                    processList[i]->cpuBurstTime[idx] = burstTime - TIME_SLICE;
                } else {
                    processList[i]->nextInterest = time + burstTime;
                    processList[i]->state = RUNNING;
                }
                //when ready queue is not empty, update the next process interesting time
                if (!isEmpty(readyQueue)) {
                    struct Process *nextProcess = getFront(readyQueue);
                    nextProcess->nextInterest = time + burstTime + CS_TIME;
                }
                processList[i]->numCS++;
                cpuFlag = true;
                //count wait time
                processList[i]->waitTimer += time - processList[i]->sumWait;
            }

            /*-----------process is preempted-----------*/
            if (processList[i]->state == PREEMPTIVE && time == processList[i]->nextInterest) {
                //add to the ready queue
                if (strcmp(RR_ADD, "BEGINNING") == 0) pushFrontQueue(readyQueue, processList[i]);
                else if (strcmp(RR_ADD, "END") == 0) pushQueue(readyQueue, processList[i]);
                //update
                processList[i]->state = READY;
                processList[i]->nextInterest = time + CS_TIME;
                processList[i]->numCS++;
                processList[i]->numPre++;
                cpuFlag = false;
                processList[i]->preFlag = true;
                //when ready queue is not empty, update the next process interesting time
                if (!isEmpty(readyQueue)) {
                    struct Process *nextProcess = getFront(readyQueue);
                    nextProcess->nextInterest = time + CS_TIME;
                }
                //output
                int idx = processList[i]->doneCPU;
                if (time <= 999) {
                    printf("time %dms: Time slice expired; process %s preempted with %0.0lfms to go ",
                           time, getProcessID(processList[i]->ID), processList[i]->cpuBurstTime[idx]);
                    fflush(stdout);
                    printQueue(readyQueue);
                }
                //count wait time
                processList[i]->sumWait = time;
            }

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
                        printf("time %dms: Process %s completed a CPU burst; %d bursts to go ",
                               time, getProcessID(processList[i]->ID), leftCPU);
                        fflush(stdout);
                        printQueue(readyQueue);
                        printf("time %dms: Process %s switching out of CPU; will block on I/O until time %0.0lfms ",
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
                    processList[i]->sumWait = time + CS_TIME;
                } else {
                    processList[i]->nextInterest = time + CS_TIME / 2.0;
                    processList[i]->sumWait = time + CS_TIME / 2.0;
                }
                processList[i]->state = READY;
            }
        }
        //////////////////algo terminating//////////////////
        //if all process done with their CPU bursts, break out of the loop
        if (allDone(processList, NUM_PROCESSES)) {
            time += CS_TIME / 2;
            printf("time %dms: Simulator ended for RR ", time);
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
    // Calculate the sum of preemption times
    int preemptionCounter = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        preemptionCounter += processList[i]->numPre;
    }
    CSCounter++;
    printAnalysis("RR", processList, NUM_PROCESSES, CSCounter, preemptionCounter, CS_TIME, f);

    //restore
    restore(processList, NUM_PROCESSES);
    freeQueue(readyQueue);
}

