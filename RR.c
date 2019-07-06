// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#include "includes.h"

void RR(struct Process* processList[], int NUM_PROCESSES, int CS_TIME, double TIME_SLICE, char* RR_ADD){

    //output each process in the process list
    outEachProcess(processList, NUM_PROCESSES);

    //copy original processlist for change
    struct Process* processListCopy[NUM_PROCESSES];
    memcpy(processListCopy, processList, sizeof(processListCopy));

    //initializing ready queue
    struct Queue* readyQueue = initizlizeQueue(NUM_PROCESSES);
    int time=0;
    while(1){
        if(time==0){
            printf("time %dms: Simulator started for RR [Q <empty>]\n",time);
        }
        //if all process done with their CPU bursts, break out of the loop
        if(allDone(processListCopy,NUM_PROCESSES)){
            //restore the count of done CPU
            for(int i=0;i<NUM_PROCESSES;i++){
                processListCopy[i]->doneCPU=0;
            }
            //break out of the loop and finishes FCFS
            printf("time %dms: Simulator ended for RR ",time);
            printQueue(readyQueue);
            break;
        }
        for(int i=0;i<NUM_PROCESSES;i++){
            //process is arriving
            if(processListCopy[i]->state==NOT_ENTERED && time==processListCopy[i]->arrivalTime){
                //add the arriving process into ready queue
                pushQueue(readyQueue,processListCopy[i]);
                printf("time %dms: Process %s arrived; added to ready queue ",
                       time,getProcessID(processList[i]->ID));
                //print out ready queue
                printQueue(readyQueue);
                //update the next interesting event time for the process
                processListCopy[i]->nextInterest=time+CS_TIME/2.0;
                processListCopy[i]->state=READY;
                //count wait time
                processListCopy[i]->sumWait=time;
            }
            //process is doing CPU burst
            if(processListCopy[i]->state==READY && time==processListCopy[i]->nextInterest && processListCopy[i]==getFront(readyQueue)){
                //get the actual CPU burst time for the current process
                int idx=processListCopy[i]->doneCPU;
                double burstTime=processListCopy[i]->cpuBurstTime[idx];
                //when the process is not preempted in the ready queue
                if(burstTime==processList[i]->cpuBurstTime[idx]){
                    printf("time %dms: Process %s started using the CPU for %lfms burst ",
                           time,getProcessID(processList[i]->ID),burstTime);
                }
                else{
                    printf("time %dms: Process %s started using the CPU with %lfms burst remaining ",
                            time,getProcessID(processList[i]->ID),burstTime);
                }
                //move the process out of the ready queue
                popQueue(readyQueue);
                //print out ready queue
                printQueue(readyQueue);
                //update
                processListCopy[i]->state=RUNNING;
                processListCopy[i]->numCS++;
                //preemption
                if(!isEmpty(readyQueue) && burstTime>TIME_SLICE){
                    //update
                    processListCopy[i]->nextInterest=time+TIME_SLICE;
                    processListCopy[i]->state=PREEMPTIVE;
                    processListCopy[i]->cpuBurstTime[idx]=burstTime-TIME_SLICE;
                    //when ready queue is not empty, update the next process interesting time
                    if(!isEmpty(readyQueue)){
                        struct Process* nextProcess=getFront(readyQueue);
                        nextProcess->nextInterest=time+TIME_SLICE+CS_TIME/2.0+1;
                    }
                }
                else{
                    processListCopy[i]->nextInterest=time+burstTime;
                    //when ready queue is not empty, update the next process interesting time
                    if(!isEmpty(readyQueue)){
                        struct Process* nextProcess=getFront(readyQueue);
                        nextProcess->nextInterest=time+burstTime+CS_TIME/2.0+1;
                    }
                }
                //count wait time
                processListCopy[i]->waitTimer+=time-processListCopy[i]->sumWait-CS_TIME/2.0;
            }
            //the current running process is preempted
            if(processListCopy[i]->state==PREEMPTIVE && time==processListCopy[i]->nextInterest){
                //add to the ready queue
                if(strcmp(RR_ADD,"BEGINNING")==0) pushFrontQueue(readyQueue,processListCopy[i]);
                else if(strcmp(RR_ADD,"END")==0) pushQueue(readyQueue,processListCopy[i]);
                processListCopy[i]->state=READY;
                processListCopy[i]->nextInterest=time+CS_TIME;
                processListCopy[i]->numCS++;
                processListCopy[i]->numPre++;
                //output
                int idx=processListCopy[i]->doneCPU;
                printf("time %dms: Time slice expired; process %s preempted with %lfms to go ",
                       time,getProcessID(processList[i]->ID),processListCopy[i]->cpuBurstTime[idx]);
                printQueue(readyQueue);
                //count wait time
                processListCopy[i]->sumWait=time;
            }
            //process is finising CPU burst
            if(processListCopy[i]->state==RUNNING && time==processListCopy[i]->nextInterest){
                //get the actual I/O burst time for the current process
                int idx=processListCopy[i]->doneCPU;
                //process is terminating
                if(idx+1==processListCopy[i]->numCPU){
                    processListCopy[i]->state=TERMINATED;
                    processListCopy[i]->doneCPU++;
                    processListCopy[i]->numCS++;
                    printf("time %dms: Process %s terminated ",
                           time,getProcessID(processList[i]->ID));
                    //print out ready queue
                    printQueue(readyQueue);
                }
                else{
                    double ioTime=processListCopy[i]->ioBurstTime[idx];
                    int leftCPU=processListCopy[i]->numCPU-processListCopy[i]->doneCPU;// #of CPU left undone
                    double finiIO=processListCopy[i]->nextInterest+ioTime;// time when the process finishing IO
                    printf("time %dms: Process %s completed a CPU burst; %d bursts to go ",
                           time,getProcessID(processList[i]->ID),leftCPU);
                    printf("time %dms: Process %s switching out of CPU; will block on I/O until time %lfms ",
                           time,getProcessID(processList[i]->ID),finiIO);
                    //print out ready queue
                    printQueue(readyQueue);
                    //update
                    processListCopy[i]->state=BLOCKED;
                    processListCopy[i]->nextInterest=time+CS_TIME/2.0+ioTime;
                    processListCopy[i]->doneCPU++;
                    processListCopy[i]->numCS++;
                }
            }
            //process is finishing I/O
            if(processListCopy[i]->state==BLOCKED && time==processListCopy[i]->nextInterest){
                //add the current process into ready queue
                pushQueue(readyQueue,processListCopy[i]);
                printf("time %dms: Process %s completed I/O; added to ready queue ",
                       time,getProcessID(processList[i]->ID));
                //print out ready queue
                printQueue(readyQueue);
                //update
                processListCopy[i]->state=READY;
                processListCopy[i]->nextInterest=time+CS_TIME/2.0;
                //count wait time
                processListCopy[i]->sumWait=time;
            }
        }


        time++;

    }

    // Calculate the sum of CS times
    int CSCounter = 0;
    for(int i = 0; i < NUM_PROCESSES; i++){
        CSCounter += processListCopy[i]->numCS;
    }
    // Calculate the sum of preemption times
    int preemptionCounter = 0;
    for(int i = 0; i < NUM_PROCESSES; i++){
        preemptionCounter += processListCopy[i]->numPre;
    }
    printAnalysis("RR", processListCopy, NUM_PROCESSES, CSCounter, preemptionCounter, CS_TIME);

    //restore
    for(int i=0;i<NUM_PROCESSES;i++){
        struct Process* curProcess=processListCopy[i];
        curProcess->waitTimer=0;
        curProcess->sumTurn=0;
        curProcess->sumWait=0;
    }
    free(readyQueue);
}

