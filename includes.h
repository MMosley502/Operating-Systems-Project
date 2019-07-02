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
enum Process_Status {READY, RUNNING, BLOCKED, PREEMPYED, TERMINATED};
enum Process_Type {CPU_BOUND, IO_BOUND};


// Structures
// Process
struct Process {
    int ID;
    enum Process_Type Type;
    enum Process_Status state;
    int burstTime;
    int waitTime;
    int blockTime;
    int burstCount;// burst how many times --> preemption times
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

#endif //OPERATING_SYSTEMS_PROJECT_INCLUDES_H
