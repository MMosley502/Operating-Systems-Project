// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#include "includes.h"

/*
 * @Arg1: seed for the random number generator
 * @Arg2: parameter@Lambda
 * @Arg3: The upper bound for valid pseudo-random numbers
 * @Arg4: parameter@n the number of processes to simulate
 * @Arg5: parameter@t_cs the time to perform a context switch
 * @Arg6: constant@Alpha for SJF and SRT
 * @Arg7: parameter@t_slice for RR
 * @Arg8: parameter@rr_add for RR
 */
int main(int argc, char** argv) {
    // Input arguments
    time_t SEED = atol(argv[1]);
    double LAMBDA = atof(argv[2]);
    int MAX = atoi(argv[3]);
    int NUM_PROCESSES = atoi(argv[4]);
    int CS_TIME = atoi(argv[5]);
    double ALPHA = atof(argv[6]);
    double TIME_SLICE = atof(argv[7]);
    int RR_ADD = atoi(argv[8]);

    // Seed the random generator
    srand48(time(&SEED));

    // Generate processes array
    struct Process* processList[NUM_PROCESSES];// Array stores all processes for simulation
    for (int i = 0; i < NUM_PROCESSES; i++) {
        struct Process* newOne = initilizer_Process();
        double r = drand48();// uniform dist [0.00,1.00)
        double x = -log(r) / LAMBDA;
        if (x > MAX) {/* avoid values that are far down the "long tail" of the distribution */
            i--;
            continue;
        }
        newOne->ID = i + 1;
        newOne->arrivalTime = floor(x);
        newOne->numCPU = (int) floor(x * 100) + 1;
        // I don't know how to get CPU burst time and IO time here?
        processList[i] = newOne;
    }

    // FCFS Algo

    // SJF Algo

    // SRT Algo

    // RR Algo


    return EXIT_SUCCESS;
}