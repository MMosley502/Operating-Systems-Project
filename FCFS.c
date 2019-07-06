// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)
#include "includes.h"

void FCFS(struct Process* processList[], int NUM_PROCESSES, int CS_TIME){

    //output each process in the process list
    outEachProcess(processList, NUM_PROCESSES);

    //initializing ready queue
    struct Queue* readyQueue = initizlizeQueue(NUM_PROCESSES);
    int time=0;
    while(1){
        if(time==0){
            printf("time %dms: Simulator started for FCFS [Q <empty>]\n",time);
        }
        //if all process done with their CPU bursts, break out of the loop
        if(allDone(processList,NUM_PROCESSES)){
            //restore the count of done CPU
            for(int i=0;i<NUM_PROCESSES;i++){
                processList[i]->doneCPU=0;
            }
            //break out of the loop and finishes FCFS
            printf("time %dms: Simulator ended for FCFS ",time);
            printQueue(readyQueue);
            break;
        }
        for(int i=0;i<NUM_PROCESSES;i++){
            //process is arriving
            if(processList[i]->state==NOT_ENTERED && time==processList[i]->arrivalTime){
                //add the arriving process into ready queue
                pushQueue(readyQueue,processList[i]);
                printf("time %dms: Process %s arrived; added to ready queue ",
                        time,getProcessID(processList[i]->ID));
                //print out ready queue
                printQueue(readyQueue);
                //update the next interesting event time for the process
                processList[i]->nextInterest=time+CS_TIME/2.0;
                processList[i]->state=READY;
                //count wait time
                processList[i]->sumWait=time;
            }
            //process is doing CPU burst
            if(processList[i]->state==READY && time==processList[i]->nextInterest && processList[i]==getFront(readyQueue)){
                //get the actual CPU burst time for the current process
                int idx=processList[i]->doneCPU;
                double burstTime=processList[i]->cpuBurstTime[idx];
                printf("time %dms: Process %s started using the CPU for %lfms burst ",
                        time,getProcessID(processList[i]->ID),burstTime);
                //move the process out of the ready queue
                popQueue(readyQueue);
                //print out ready queue
                printQueue(readyQueue);
                //when ready queue is not empty, update the next process interesting time
                if(!isEmpty(readyQueue)){
                    struct Process* nextProcess=getFront(readyQueue);
                    nextProcess->nextInterest=time+burstTime+CS_TIME/2.0+1;
                }
                //update
                processList[i]->state=RUNNING;
                processList[i]->nextInterest=time+burstTime;
                processList[i]->numCS++;
                //count wait time
                processList[i]->waitTimer+=time-processList[i]->sumWait-CS_TIME/2.0;
            }
            //process is finising CPU burst
            if(processList[i]->state==RUNNING && time==processList[i]->nextInterest){
                //get the actual I/O burst time for the current process
                int idx=processList[i]->doneCPU;
                //process is terminating
                if(idx+1==processList[i]->numCPU){
                    processList[i]->state=TERMINATED;
                    processList[i]->doneCPU++;
                    processList[i]->numCS++;
                    printf("time %dms: Process %s terminated ",
                           time,getProcessID(processList[i]->ID));
                    //print out ready queue
                    printQueue(readyQueue);
                }
                else{
                    double ioTime=processList[i]->ioBurstTime[idx];
                    int leftCPU=processList[i]->numCPU-processList[i]->doneCPU;// #of CPU left undone
                    double finiIO=processList[i]->nextInterest+ioTime;// time when the process finishing IO
                    printf("time %dms: Process %s completed a CPU burst; %d bursts to go ",
                           time,getProcessID(processList[i]->ID),leftCPU);
                    printQueue(readyQueue);
                    printf("time %dms: Process %s switching out of CPU; will block on I/O until time %lfms ",
                           time,getProcessID(processList[i]->ID),finiIO);
                    //print out ready queue
                    printQueue(readyQueue);
                    //update
                    processList[i]->state=BLOCKED;
                    processList[i]->nextInterest=time+CS_TIME/2.0+ioTime;
                    processList[i]->doneCPU++;
                    processList[i]->numCS++;
                }
            }
            //process is finishing I/O
            if(processList[i]->state==BLOCKED && time==processList[i]->nextInterest){
                //add the current process into ready queue
                pushQueue(readyQueue,processList[i]);
                printf("time %dms: Process %s completed I/O; added to ready queue ",
                        time,getProcessID(processList[i]->ID));
                //print out ready queue
                printQueue(readyQueue);
                //update
                processList[i]->state=READY;
                processList[i]->nextInterest=time+CS_TIME/2.0;
                //count wait time
                processList[i]->sumWait=time;
            }

        }


        time++;

    }
    // Calculate the sum of CS times
    int CSCounter = 0;
    for(int i = 0; i < NUM_PROCESSES; i++){
        CSCounter += processList[i]->numCS;
    }
    // No preemption in FCFS, just set as 0
    printAnalysis("FCFS", processList, NUM_PROCESSES, CSCounter, 0, CS_TIME);

    //restore
    for(int i=0;i<NUM_PROCESSES;i++){
        struct Process* curProcess=processList[i];
        curProcess->waitTimer=0;
        curProcess->sumTurn=0;
        curProcess->sumWait=0;
    }
    free(readyQueue);
}

