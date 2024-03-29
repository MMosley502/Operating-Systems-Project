// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#include "includes.h"


//output each process in the process list
// Print as the ascending order of process ID
void outEachProcess(struct Process *processList[], int NUM_PROCESSES) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if(processList[i]->numCPU==1){
            printf("Process %s [NEW] (arrival time %d ms) %d CPU burst\n",
                   getProcessID(processList[i]->ID), processList[i]->arrivalTime, processList[i]->numCPU);
            fflush(stdout);
        }
        else{
            printf("Process %s [NEW] (arrival time %d ms) %d CPU bursts\n",
                   getProcessID(processList[i]->ID), processList[i]->arrivalTime, processList[i]->numCPU);
            fflush(stdout);
        }
    }
}

//output each process in the process list for SJF and SRT
// Print extra estimate time
// Print as the ascending order of process ID
void outEPS(struct Process *processList[], int NUM_PROCESSES) {
    for (int i = 0; i < NUM_PROCESSES; i++) {
        if(processList[i]->numCPU==1){
            printf("Process %s [NEW] (arrival time %d ms) %d CPU burst (tau %0.0fms)\n",
                   getProcessID(processList[i]->ID), processList[i]->arrivalTime, processList[i]->numCPU,
                   processList[i]->nextEstBurst);
            fflush(stdout);
        }
        else{
            printf("Process %s [NEW] (arrival time %d ms) %d CPU bursts (tau %0.0fms)\n",
                   getProcessID(processList[i]->ID), processList[i]->arrivalTime, processList[i]->numCPU,
                   processList[i]->nextEstBurst);
            fflush(stdout);
        }
    }
}

/*
 * Converting the Process ID from number to alpabetic
 */
char *getProcessID(int numberID) {
    char *Alphabetic[26] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q",
                            "R", "S", "T", "U", "V", "W", "X", "Y", "Z"};
    return Alphabetic[numberID - 1];
}


/*
 * Function for general printing of analysis
 * If any argument is not applied to a specific algo
 * Just give 0
 */
void printAnalysis(char *algo, struct Process *processList[], int NUM_PROCESSES, int CSCounter,
                   int preemptionCounter, int CS_TIME, FILE *f) {
    double aveBurst = computeAveBurst(processList, NUM_PROCESSES);
    double aveWait = computeAveWait(processList, NUM_PROCESSES);
    double aveTurnAround = computeAveTurnAround(processList, CSCounter, NUM_PROCESSES, CS_TIME);

    fprintf(f,"Algorithm %s\n", algo);
    fprintf(f,"-- average CPU burst time: %0.3f ms\n", aveBurst);
    fprintf(f,"-- average wait time: %0.3f ms\n", aveWait);
    fprintf(f,"-- average turnaround time: %0.3f ms\n", aveTurnAround);
    fprintf(f,"-- total number of context switches: %d\n", CSCounter);
    fprintf(f,"-- total number of preemptions: %d\n", preemptionCounter);
}

double computeAveWait(struct Process *processList[], int NUM_PROCESSES) {
    double sum = 0;
    int sumCPU = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        sum += processList[i]->waitTimer;
        sumCPU += processList[i]->numCPU;
    }
    return sum / sumCPU;
}


double computeAveBurst(struct Process *processList[], int NUM_PROCESSES) {
    double sum = 0;
    int sumCPU = 0;
    for (int i = 0; i < NUM_PROCESSES; i++) {
        sum += processList[i]->maxCPUTime;
        sumCPU += processList[i]->numCPU;
    }
    return sum / sumCPU;
}

double computeAveTurnAround(struct Process *processList[], int CSCounter, int NUM_PROCESSES, int CS_TIME) {
//    double sum = 0;
//    int sumCPU = 0;
//    for (int i = 0; i < NUM_PROCESSES; i++) {
//        sum += processList[i]->waitTimer;
//        sum += processList[i]->maxCPUTime;
//        sumCPU += processList[i]->numCPU;
//    }
//    sum += (CSCounter * (CS_TIME /2.0));// Total turnaround time
//    return sum / sumCPU;
    double sum = 0;
    int sumCPU = 0;
    for(int i=0;i<NUM_PROCESSES;i++){
        sum += processList[i]->end - processList[i]->arrivalTime - processList[i]->maxIOTime + CS_TIME/2.0;
        sumCPU += processList[i]->numCPU;
    }
    return sum / sumCPU;
}
