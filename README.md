# Operating Systems CPU Scheduling Simulation
2019Summer CSCI 4210 Operating Systems Group Project


[Project Description](https://github.com/JadeWang96/Operating-Systems-Project/blob/master/project.pdf)
* This project implements a rudimentary simulation of an operating system and focuses on on processes, 
assumed to be resident in memory, waiting to use the CPU.
* Application Algorithm: First Come First Served, Shorted Job First, 
Shortest Remaining Time, Robin Round


## Authors
Collaborator: [@abbylululu](https://github.com/abbylululu) [@JadeWang96](https://github.com/JadeWang96)


## File Structure

1. includes.h
2. main.c
3. FCFS.c
4. SJF.c
5. SRT.c
6. RR.c
7. helper.c
8. Queue.c
9. output.c

### Prerequisites
gcc compiler 7.4.0 - 1ubuntu1~18.04\
Optional: Ubuntu(Linux) v18.04.2


## Running the tests

!/bin/sh

1. test _1 compile

gcc -Wall project.c -lm -D DISPLAY_MAX_T=1000

2. test _2\
a.out 2 0.01 256 1 4 0.5 128 > output02.txt\
mv simout.txt simout02.txt

3. test _3\
a.out 2 0.01 256 2 4 0.5 128 > output03.txt\
mv simout.txt simout03.txt

4. test _4\
a.out 2 0.01 256 16 4 0.5 128 > output04.txt\
mv simout.txt simout04.txt

5. test _5\
a.out 64 0.001 4096 8 4 0.5 2048 > output05.txt\
mv simout.txt simout05.txt

## Acknowledgments

* Professor G.
* Professor H.
* Sonny :)


