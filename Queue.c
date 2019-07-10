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
struct Queue *initizlizeQueue(unsigned int capacity) {
    struct Queue *Q = calloc(1, sizeof(struct Queue));
    Q->capacity = capacity;
    Q->front = 0;// the index of front
    Q->rear = capacity - 1;// the index of rear
    Q->size = 0;
    Q->array = calloc(capacity, sizeof(struct Process *));

    return Q;
}

/*
 * Whether the queue is empty
 */
bool isEmpty(struct Queue *Q) {
    return Q->size == 0;
}

/*
 * Whether the queue is full
 */
bool isFull(struct Queue *Q) {
    return Q->size == Q->capacity;
}

/*
 * Add a process to the end of queue
 */
void pushQueue(struct Queue *Q, struct Process *item) {
    if (isFull(Q)) return;
    Q->rear = (Q->rear + 1) % (Q->capacity);
    Q->array[Q->rear] = item;
    Q->size++;
}

/*
 * Add a process to the front of queue
 */
void pushFrontQueue(struct Queue *Q, struct Process *item) {
    if (isFull(Q)) return;
    if (Q->front - 1 < 0) {
        Q->front = Q->capacity - 1;
        Q->array[Q->front] = item;
    } else {
        Q->front--;
        Q->array[Q->front] = item;
    }
    Q->size++;
}

/*
 * Remove a process from the head of queue
 */
struct Process *popQueue(struct Queue *Q) {
    if (isEmpty(Q)) return NULL;
    struct Process *item = Q->array[Q->front];
    Q->front = (Q->front + 1) % (Q->capacity);
    Q->size--;
    return item;
}

/*
 * Get the front process
 */
struct Process *getFront(struct Queue *Q) {
    if (isEmpty(Q)) return NULL;
    return Q->array[Q->front];
}

/*
 * Get the rear process
 */
struct Process *getRear(struct Queue *Q) {
    if (isEmpty(Q)) return NULL;
    return Q->array[Q->rear];
}

/*
 * Print out the queue
 */
void printQueue(struct Queue *Q) {
    if (isEmpty(Q)) {
        printf("[Q <empty>]\n");
        fflush(stdout);
    } else {
        printf("[Q");
        fflush(stdout);
        if (Q->front > Q->rear) {
            for (int i = Q->front; i < Q->capacity; i++) {
                printf(" %s", getProcessID(Q->array[i]->ID));
                fflush(stdout);
            }
            for (int i = 0; i <= Q->rear; i++) {
                printf(" %s", getProcessID(Q->array[i]->ID));
                fflush(stdout);
            }
        } else {
            for (int i = Q->front; i <= Q->rear; i++) {
                printf(" %s", getProcessID(Q->array[i]->ID));
                fflush(stdout);
            }
        }
        printf("]\n");
        fflush(stdout);
    }
}

/*
 * Operating after every push
 * sort the Queue by estBurstTime, if the estBurstTime are same, sort by ID number
 */
void sortQueue(struct Queue *Q) {
    if (Q->size == 1 || Q->size == 0) return;

    struct Process **copyQ = calloc(Q->capacity, sizeof(struct Process *));
    int pos = 0;
    if (Q->rear < Q->front) {
        for (int i = Q->front; i < Q->capacity; i++) {
            copyQ[pos++] = Q->array[i];
        }
        for (int i = 0; i <= Q->rear; i++) {
            copyQ[pos++] = Q->array[i];
        }
    } else {
        for (int i = Q->front; i <= Q->rear; i++) {
            copyQ[pos++] = Q->array[i];
        }
    }

    struct Process *change;
    // bubble sort
    // Reference: https://www.geeksforgeeks.org/bubble-sort/
    // Sort burst time
    for (int i = 0; i < Q->size - 1; i++) {
        for (int k = 0; k < Q->size - i - 1; k++) {
            if (copyQ[k]->nextEstBurst > copyQ[k + 1]->nextEstBurst) {
                change = copyQ[k];
                copyQ[k] = copyQ[k + 1];
                copyQ[k + 1] = change;
            }
        }
    }
    // Sort ID
    for (int i = 0; i < Q->size - 1; i++) {
        for (int k = 0; k < Q->size - i - 1; k++) {
            if ((copyQ[k]->nextEstBurst == copyQ[k + 1]->nextEstBurst) && (copyQ[k]->ID > copyQ[k + 1]->ID)) {
                change = copyQ[k];
                copyQ[k] = copyQ[k + 1];
                copyQ[k + 1] = change;
            }
        }
    }


    for (int i = 0; i < Q->size; i++) {
        Q->array[i] = copyQ[i];
    }
    Q->front = 0;
    Q->rear = pos - 1;


    free(copyQ);
}

void freeQueue(struct Queue *Q) {
    free(Q->array);
    free(Q);
}

/*
 * advance processes' next interesting time by 1, when they are in the queue
 * except for the first process
 */
void advQueue(struct Queue *Q) {
    if (Q->size == 1 || Q->size == 0) return;

    if (Q->rear < Q->front) {
        for (int i = Q->front + 1; i < Q->capacity; i++) {
            struct Process *curProcess = Q->array[i];
            curProcess->nextInterest++;
        }
    } else {
        for (int i = Q->front + 1; i <= Q->rear; i++) {
            struct Process *curProcess = Q->array[i];
            curProcess->nextInterest++;
        }
    }
}
