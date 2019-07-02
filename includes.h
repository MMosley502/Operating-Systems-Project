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
    int burstTime;// Actual CPU burst time
    int waitTime;// wait time counter
    int blockTime;// block time counter
    int numCPU;// number of CPU bursts
};

// Seal all return value from each algo
struct Algo {
    double aveCPUBurst; // average CPU burst time
    double aveWait;// average wait time
    double aveTurnAround;// average turnaround time
    int numCS;// total number of context switches
    int numPreemption;// total number of preemptions
};

// Function prototype
// helper.c
struct Process* initilizer_Process();

// SJF.c

// SRT.c

// RR.c

// output.c

#endif //OPERATING_SYSTEMS_PROJECT_INCLUDES_H
