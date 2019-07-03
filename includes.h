// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#ifndef OPERATING_SYSTEMS_PROJECT_INCLUDES_H
#define OPERATING_SYSTEMS_PROJECT_INCLUDES_H
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
enum Process_ID {A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q,
                R, S, T, U, V, W, X, Y, Z};
enum Process_Status {READY, RUNNING, BLOCKED, PREEMPYED, TERMINATED};
enum Process_Type {CPU_BOUND, IO_BOUND};


// Structures
// Process
struct Process {
    int ID;// from 1 to 26
    enum Process_Type Type;
    enum Process_Status state;
    int arrivalTime;
    double maxCPUTime;// total CPU burst time
    double maxIOTime;
    double waitTime;// wait time counter
    double blockTime;// block time counter
    int numCPU;// number of CPU bursts
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

// Function prototype
// helper.c
struct Process* initilizer_Process();
double randomTime(double* Time, int numCPU, int MAX, double LAMBDA);

// SJF.c
void SJF(struct Process* processList, int CS_TIME, double ALPHA);

// SRT.c

// RR.c

// Queue.c
struct Queue* initizlizeQueue(unsigned int capacity);
bool isEmpty(struct Queue* Q);
bool isFull(struct Queue* Q);
void pushQueue(struct Queue* Q, struct Process* item);
struct Process* popQueue(struct Queue* Q);
struct Process* getFront(struct Queue* Q);
struct Process* getRear(struct Queue* Q);

// output.c

#endif //OPERATING_SYSTEMS_PROJECT_INCLUDES_H
