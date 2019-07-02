// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#include "includes.h"


/*
 * @Arg: None
 * Initializing a Process structure
 * @Return: A pointer to struct Process
 * Need to free memory
 */
struct Process* initilizer_Process() {
    struct Process* newOne = calloc(1, sizeof(struct Process));

    newOne->ID = -1;
    newOne->Type = (enum Process_Type) READY;
    newOne->state = (enum Process_Status) CPU_BOUND;
    newOne->arrivalTime = -1;
    newOne->burstTime = -1;
    newOne->waitTime = 0;
    newOne->blockTime = 0;
    newOne->numCPU = -1;
}