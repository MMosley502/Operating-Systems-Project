cmake_minimum_required(VERSION 3.10)
project(Operating-Systems-Project C)

set(CMAKE_C_STANDARD 11)

add_executable(Operating-Systems-Project main.c includes.h RR.c SJF.c SRT.c output.c helper.c Queue.c FCFS.c)
#add_executable(Operating-Systems-Project main.c includes.h helper.c SJF.c output.c Queue.c)

target_link_libraries(Operating-Systems-Project m)
