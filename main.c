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
int main(int argc, char **argv) {
    setvbuf(stdout, NULL, _IONBF, 0);
    // Input arguments
    time_t SEED = atol(argv[1]);
    double LAMBDA = atof(argv[2]);
    int MAX = atoi(argv[3]);
    int NUM_PROCESSES = atoi(argv[4]);
    int CS_TIME = atoi(argv[5]);
    double ALPHA = atof(argv[6]);
    double TIME_SLICE = atof(argv[7]);
    char *RR_ADD;
    if (argc == 8) RR_ADD = "END";
    else RR_ADD = argv[8];

    // Seed the random generator
    srand48(time(&SEED));

    // Generate processes array
    struct Process *processList[NUM_PROCESSES];// Array stores all processes for simulation

    for (int i = 0; i < NUM_PROCESSES; i++) {

        processList[i] = initilizer_Process();

        double r = drand48();// uniform dist [0.00,1.00)
        double x = -log(r) / LAMBDA;
        if (x > MAX) {/* avoid values that are far down the "long tail" of the distribution */
            i--;
            continue;
        }

        processList[i]->ID = i + 1;// ID start from 1 and later for matching with A-Z
        processList[i]->arrivalTime = (int) floor(x);
        processList[i]->numCPU = (int) floor(r * 100) + 1;

        // Random for CPU burst time
        processList[i]->maxCPUTime = randomTime(processList[i]->cpuBurstTime, processList[i]->numCPU, MAX, LAMBDA);

        //copy CPU burst array for restoring
        for (int q = 0; q < 101; q++) {
            processList[i]->cpuBurstTimeCopy[q] = processList[i]->cpuBurstTime[q];
        }

        // Random for IO burst time
        randomTime(processList[i]->ioBurstTime, processList[i]->numCPU, MAX, LAMBDA);
        processList[i]->ioBurstTime[processList[i]->numCPU - 1] = 0;// Last CPU burst doesn't have IO burst time

        //Estimate CPU burst time for SJF & SRT
        processList[i]->nextEstBurst = ceil(1 / LAMBDA);
        processList[i]->initialEstBurst = ceil(1 / LAMBDA);


    }

#if 0
    //DEBUG
    for(int i=0;i<processList[0]->numCPU;i++){
        printf("%0.0f\n",processList[0]->cpuBurstTime[i]);
    }
#endif

    //open a file for writing algorithm analysis
    FILE *f = fopen("simout.txt", "w");
    if (f == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

#if 1
    // FCFS Algo
    FCFS(processList, NUM_PROCESSES, CS_TIME, f);
    printf("\n");
    fflush(stdout);

    // SJF Algo
    SJF(processList, NUM_PROCESSES, CS_TIME, ALPHA, f);
    printf("\n");
    fflush(stdout);

    // SRT Algo
    SRT(processList, NUM_PROCESSES, CS_TIME, ALPHA, f);
    printf("\n");
    fflush(stdout);

    // RR Algo
    RR(processList, NUM_PROCESSES, CS_TIME, TIME_SLICE, RR_ADD, f);

    freeProcessList(processList, NUM_PROCESSES);
#endif

    return EXIT_SUCCESS;
}
