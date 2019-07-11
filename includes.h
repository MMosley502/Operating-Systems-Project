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
#include <fcntl.h>

// Enumeration
enum Process_Status {
    NOT_ENTERED, READY, RUNNING, BLOCKED, PREEMPTIVE, TERMINATED
};

//================================================================
// Structures
// Process
struct Process {
    // Variables
    int ID;// from 1 to 26
    enum Process_Status state;
    int arrivalTime;
    int end;
    int numCPU;// number of CPU bursts
    int doneCPU;// number of CPU bursts done executing
    double nextInterest;//time point for next interesting event
    bool preFlag;// flag to indicate preemption
    bool inCS;

    // Estimates
    double initialEstBurst;
    double nextEstBurst;
    double nextActualBurst;
    double oldEstBurst;

    // Counters
    double readyStart;
    double burstStart;
    double waitTimer;// wait time counter
    double burstTimer;// burst time counter
    double maxCPUTime;// sum of all CPU burst time
    double maxIOTime;// sum of all IO burst time
    double sumWait;// sum of wait time
    int numCS;// number of context switches
    int numPre;// number of preemption

    double cpuBurstTime[101];// Actual CPU burst time
    double cpuBurstTimeCopy[101];// copy of CPU burst time array for restoring
    double ioBurstTime[101];//Actual I/O burst time
};

// Queue
struct Queue {
    int front;
    int rear;
    int size;
    unsigned int capacity;
    struct Process **array;
};

//================================================================
// Function prototype
// helper.c
struct Process *initilizer_Process();

double randomTime(double Time[], int numCPU, int MAX, double LAMBDA);

double estimateTime(struct Process *newOne, double ALPHA, int pos);

double estimateTimeSRT(struct Process *newOne, double ALPHA, int pos);

bool allDone(struct Process *processList[], int NUM_PROCESSES);

void freeProcessList(struct Process *processList[], int NUM_PROCESSES);

bool isPreemptive(int currentRunningPos, struct Process *processListCopy[], struct Queue *readyQueue, int time,
                  int NUM_PROCESSES);

bool isPreemptiveRunning(int currentRunningPos, struct Process *processListCopy[],
                         struct Queue *readyQueue, int time, int NUM_PROCESSES);

void restore(struct Process *processList[], int NUM_PROCESSES);

double randomNumber(int MAX, double LAMBDA );

// SJF.c
void SJF(struct Process *processList[], int NUM_PROCESSES, int CS_TIME, double ALPHA, FILE* f);

// SRT.c
void SRT(struct Process *processList[], int NUM_PROCESSES, int CS_TIME, double ALPHA, FILE* f);

//FCFS.c
void FCFS(struct Process *processList[], int NUM_PROCESSES, int CS_TIME, FILE* f);

// RR.c
void RR(struct Process *processList[], int NUM_PROCESSES, int CS_TIME, double TIME_SLICE, char *RR_ADD, FILE* f);

// Queue.c
struct Queue *initizlizeQueue(unsigned int capacity);

bool isEmpty(struct Queue *Q);

bool isFull(struct Queue *Q);

void pushQueue(struct Queue *Q, struct Process *item);

void pushFrontQueue(struct Queue *Q, struct Process *item);

struct Process *popQueue(struct Queue *Q);

struct Process *getFront(struct Queue *Q);

struct Process *getRear(struct Queue *Q);

void printQueue(struct Queue *Q);

void sortQueue(struct Queue *Q);

void freeQueue(struct Queue *Q);

// output.c
void outEachProcess(struct Process *processList[], int NUM_PROCESSES);

void outEPS(struct Process *processList[], int NUM_PROCESSES);

char *getProcessID(int numberID);

void printAnalysis(char *algo, struct Process *processList[], int NUM_PROCESSES, int CSCounter,
                   int preemptionCounter, int CS_TIME, FILE* f);

double computeAveBurst(struct Process *processList[], int NUM_PROCESSES);

double computeAveWait(struct Process *processList[], int NUM_PROCESSES);

double computeAveTurnAround(struct Process *processList[], int CSCounter, int NUM_PROCESSES, int CS_TIME);


#endif //OPERATING_SYSTEMS_PROJECT_INCLUDES_H
