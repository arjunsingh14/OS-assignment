typedef struct {
    int data[100];
    int front;
    int rear;
} Queue;
void enqueue(Queue *q, int p, int w) {
    if ((q->rear + 1) % w == q->front) {
        // queue is full
        return;
    }
    if (q->front == -1) {
        // queue is empty
        q->front = 0;
        q->rear = 0;
        q->data[0] = p;
        return;
    }
    q->rear = (q->rear + 1) % w;
    q->data[q->rear] = p;
    if (q->rear == q->front) {
        // queue has only one element
        q->front = q->rear;
    }
    return;
}

int dequeue(Queue *q, int w) {
    if (q->front == -1){
        // queue is empty
        return -1;
    }
    int p = q->data[q->front];
    if (q->front == q->rear) {
        // queue has only one element
        q->front = -1;
        q->rear = -1;
    } else {
        q->front = (q->front + 1) % w;
    }
    return p;
}
