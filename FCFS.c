// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)
#include "includes.h"

void FCFS(struct Process* processList[], int NUM_PROCESSES, int CS_TIME){

    //output each process in the process list
    for(int i=0;i<NUM_PROCESSES;i++){
        printf("Process %d [NEW] (arrival time %d ms) %d CPU bursts\n",
                processList[i]->Type,processList[i]->arrivalTime,processList[i]->numCPU);
    }

    //initializing ready queue
    struct Queue* readyQueue = initizlizeQueue(NUM_PROCESSES);
    int time=0;
    while(1){
        if(time==0){
            printf("time %dms: Simulator started for FCFS [Q <empty>]\n",time);
        }
        //if all process done with their CPU bursts, break out of the loop
        if(allDone){
            //restore the count of done CPU
            for(int i=0;i<NUM_PROCESSES;i++){
                processList[i]->doneCPU=processList[i]->numCPU;
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
                printf("time %dms: Process %d arrived; added to ready queue ",
                        time,processList[i]->Type);
                //print out ready queue
                printQueue(readyQueue);
                //update the next interesting event time for the process
                processList[i]->nextInterest+=CS_TIME/2;
                processList[i]->state=READY;
            }
            //process is doing CPU burst
            if(processList[i]->state==READY && time==processList[i]->nextInterest){
                //get the actual CPU burst time for the current process
                int idx=processList[i]->doneCPU;
                double burstTime=processList[i]->cpuBurstTime[idx];
                printf("time %dms: Process %d started using the CPU for %lfms burst ",
                        time,processList[i]->Type,burstTime);
                //move the process out of the ready queue
                popQueue(readyQueue);
                //print out ready queue
                printQueue(readyQueue);
                //update
                processList[i]->state=RUNNING;
                processList[i]->nextInterest+=burstTime;
            }
            //process is finising CPU burst
            if(processList[i]->state==RUNNING && time==processList[i]->nextInterest){
                //get the actual I/O burst time for the current process
                int idx=processList[i]->doneCPU;
                double ioTime=processList[i]->ioBurstTime[idx];
                int leftCPU=processList[i]->numCPU-processList[i]->doneCPU;// #of CPU left undone
                double finiIO=processList[i]->nextInterest+ioTime;// time when the process finishing IO
                printf("time %dms: Process %d completed a CPU burst; %d bursts to go ",
                        time,processList[i]->Type,leftCPU);
                printf("time %dms: Process %d switching out of CPU; will block on I/O until time %lfms ",
                        time,processList[i]->Type,finiIO);
                //print out ready queue
                printQueue(readyQueue);
                //update
                processList[i]->state=BLOCKED;
                processList[i]->nextInterest+=ioTime;
                processList[i]->doneCPU++;
            }
            //process is finishing I/O
            if(processList[i]->state==BLOCKED && time==processList[i]->nextInterest){
                //add the current process into ready queue
                pushQueue(readyQueue,processList[i]);
                printf("time %dms: Process %d completed I/O; added to ready queue ",
                        time,processList[i]->Type);
                //print out ready queue
                printQueue(readyQueue);
                //update
                processList[i]->state=READY;
                processList[i]->nextInterest+=CS_TIME/2;
            }
            //process is terminating
            if(processList[i]->doneCPU==processList[i]->numCPU){
                printf("time %dms: Process %d terminated ",
                        time,processList[i]->Type);
                //print out ready queue
                printQueue(readyQueue);
            }

        }


        time++;

    }

}

