// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#ifndef OPERATING_SYSTEMS_PROJECT_INCLUDES_H
#define OPERATING_SYSTEMS_PROJECT_INCLUDES_H
#define MAXPROCESS 26
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <limits.h>

// Enumeration
enum Process_Status {NOT_ENTERED, READY, RUNNING, BLOCKED, PREEMPYED, TERMINATED};
//enum Process_Type {CPU_BOUND, IO_BOUND};

//================================================================
// Structures
// Process
struct Process {
    // Variables
    int ID;// from 1 to 26
//    enum Process_Type Type;
    enum Process_Status state;
    int arrivalTime;
    double maxCPUTime;// total CPU burst time
    double maxIOTime;
    int numCPU;// number of CPU bursts
    int doneCPU;// number of CPU bursts done executing
    double nextInterest;//time point for next interesting event

    // Estimates
    double* estCPUBurst;

    // Counters
    double waitTime;// wait time counter
    double blockTime;// block time counter
    double* cpuBurstTime;// Actual CPU burst time
    double* ioBurstTime;//Actual I/O burst time
};

// Queue
struct Queue {
    int front;
    int rear;
    int size;
    unsigned int capacity;
    struct Process** array;
};
//================================================================
// Function prototype
// helper.c
struct Process* initilizer_Process();
double randomTime(double* Time, int numCPU, int MAX, double LAMBDA);
void estimateTime(struct Process* newOne, double ALPHA, int pos);
void arrayToQueue(struct Process* processListCopy[], int NUM_PROCESSES, struct Queue* readyQueue);
bool allDone(struct Process* processList[], int NUM_PROCESSES);

// SJF.c
void SJF(struct Process* processList[], int NUM_PROCESSES, int CS_TIME, double ALPHA);
int compareTime(const void * a, const void * b);

// SRT.c

//FCFS.c
void FCFS(struct Process* processList[], int NUM_PROCESSES, int CS_TIME);

// RR.c

// Queue.c
struct Queue* initizlizeQueue(unsigned int capacity);
bool isEmpty(struct Queue* Q);
bool isFull(struct Queue* Q);
void pushQueue(struct Queue* Q, struct Process* item);
struct Process* popQueue(struct Queue* Q);
struct Process* getFront(struct Queue* Q);
struct Process* getRear(struct Queue* Q);
void printQueue(struct Queue* Q);

// output.c
int compareArrival(const void * a, const void * b);
void outEachProcess(struct Process* processList[], int NUM_PROCESSES);
char* getProcessID(int numberID);



#endif //OPERATING_SYSTEMS_PROJECT_INCLUDES_H
