#ifndef QUEUE_H_
#define QUEUE_H_



typedef struct {
    int data[100];
    int front;
    int rear;
    int size;
} Queue;

void enqueue(Queue *q, int p, int w);

int dequeue(Queue *q, int w);

#endif
