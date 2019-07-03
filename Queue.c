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
    struct Process* array;
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

