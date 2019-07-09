// CSCI 4210 Operating Systems
// 2019 Summer
// Ming Lu (lum8) & Yujue Wang (wangy66)

#include "includes.h"

/*
 * Implementation of handmade Queue data structure in C
 * Reference: https://www.geeksforgeeks.org/queue-set-1introduction-and-array-implementation/
 */

/*
struct Queue {
    int front;
    int rear;
    int size;
    unsigned int capacity;
    struct Process** array;
};
*/

// Functions for Queue
/*
 * Initializing an empty queue
 */
struct Queue* initizlizeQueue(unsigned int capacity) {
    struct Queue* Q = calloc(1, sizeof(struct Queue));
    Q->capacity = capacity;
    Q->front = 0;// the index of front
    Q->rear = capacity - 1;// the index of rear
    Q->size = 0;
    Q->array = calloc(capacity, sizeof(struct Process*));

    return Q;
}

/*
 * Whether the queue is empty
 */
bool isEmpty(struct Queue* Q) {
    return Q->size == 0;
}

/*
 * Whether the queue is full
 */
bool isFull(struct Queue* Q) {
    return Q->size == Q->capacity;
}

/*
 * Add a process to the end of queue
 */
void pushQueue(struct Queue* Q, struct Process* item) {
    if (isFull(Q)) return;
    Q->rear = (Q->rear + 1) % (Q->capacity);
    Q->array[Q->rear] = item;
    Q->size++;
}

/*
 * Add a process to the front of queue
 */
void pushFrontQueue(struct Queue* Q, struct Process* item){
    if (isFull(Q)) return;
    if(Q->front-1<0) {
        Q->front=Q->capacity-1;
        Q->array[Q->front] = item;
    }
    else {
        Q->front--;
        Q->array[Q->front] = item;
    }
    Q->size++;
}

/*
 * Remove a process from the head of queue
 */
struct Process* popQueue(struct Queue* Q) {
    if (isEmpty(Q)) return NULL;
    struct Process* item = Q->array[Q->front];
    Q->front = (Q->front + 1) % (Q->capacity);
    Q->size--;
    return item;
}

/*
 * Get the front process
 */
struct Process* getFront(struct Queue* Q) {
    if (isEmpty(Q)) return NULL;
    return Q->array[Q->front];
}

/*
 * Get the rear process
 */
struct Process* getRear(struct Queue* Q) {
    if (isEmpty(Q)) return NULL;
    return Q->array[Q->rear];
}

/*
 * Print out the queue
 */
void printQueue(struct Queue* Q){
    if (isEmpty(Q)){
        printf("[Q <empty>]\n");
    }
    else{
        printf("[Q");
        if(Q->front>Q->rear){
            for(int i = Q->front; i < Q->capacity; i++){
                printf(" %s", getProcessID(Q->array[i]->ID));
            }
            for(int i = 0; i <= Q->rear; i++){
                printf(" %s", getProcessID(Q->array[i]->ID));
            }
        }
        else{
            for(int i = Q->front; i <= Q->rear; i++){
                printf(" %s", getProcessID(Q->array[i]->ID));
            }
        }
        printf("]\n");
    }
}

/*
 * Operating after every push
 * sort the Queue by estBurstTime, if the estBurstTime are same, sort by ID number
 */
void sortQueue(struct Queue* Q) {
    if (Q->size == 1 || Q->size == 0) return;

//    for (int j = 0; j < Q->capacity; j++) {
//        if (Q->array[j]) {
//            printf("!Q array %d,  ID is %d\n", j, Q->array[j]->ID);
//        } else {
//            printf("!Q array %d NULL\n", j);
//        }
//    }

    struct Process** copyQ = calloc(Q->capacity, sizeof(struct Process*));
    int pos = 0;
    if (Q->rear < Q->front) {
        for (int i = 0; i < Q->capacity; i++){
            if (Q->array[i]) {
                copyQ[pos] = Q->array[i];
                pos++;
            }
            Q->array[i] = NULL;
        }
        memcpy(Q->array, copyQ, sizeof(Q->capacity));
    }

    int start = Q->front;
    int end = Q->rear;
    struct Process* temp[Q->size];
    int temp_pos = 0;
    for (int i = start; i <= end; i++) {
        temp[temp_pos] = Q->array[i];
        temp_pos++;
    }
    // Sort by estBurst time
    qsort(temp, Q->size, sizeof(struct Process*), compareTime);
    struct Process* change;
    while (1) {
        for (int i = 0; i < Q->size - 1; i++) {
            if ((temp[i]->nextEstBurst == temp[i + 1]->nextEstBurst) && (temp[i]->ID > temp[i + 1]->ID)) {
                change = temp[i];
                temp[i] = temp[i + 1];
                temp[i + 1] = change;
            }
        }
        if (isRight(temp, Q->size)) {
            break;
        }
    }
    temp_pos = 0;
    for (int i = start; i <= end; i++) {
        Q->array[i] = temp[temp_pos];
        temp_pos++;
    }
    free(copyQ);
}

/*
 * Operating after every push
 * when processes are arriving at the same time, sort by ID number
 */
void SQ(struct Queue* Q){
    
}

/*
 * Check whether the readyQueue in right order
 */
bool isRight(struct Process* temp[], int length) {
    for (int i = 0; i < length - 1; i++) {
        if ((temp[i]->nextEstBurst > temp[i + 1]->nextEstBurst) ||
        ((temp[i]->nextEstBurst == temp[i + 1]->nextEstBurst) && (temp[i]->ID > temp[i + 1]->ID))) {
            return false;
        }
    }
}