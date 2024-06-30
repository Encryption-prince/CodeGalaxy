#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Define a structure for the queue
struct Queue {
    int items[MAX_SIZE];
    int front;
    int rear;
};

// Function to initialize the queue
void initQueue(struct Queue *queue) {
    queue->front = -1; // Initialize front of the queue
    queue->rear = -1;  // Initialize rear of the queue
}

// Function to check if the queue is full
int isFull(struct Queue *queue) {
    return (queue->rear == MAX_SIZE - 1);
}

// Function to check if the queue is empty
int isEmpty(struct Queue *queue) {
    return (queue->front == -1 && queue->rear == -1);
}

// Function to enqueue (insert) an element into the queue
void enqueue(struct Queue *queue, int item) {
    if (isFull(queue)) {
        printf("Queue overflow! Cannot enqueue %d\n", item);
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0; // If queue is empty, set front to 0
    }
    queue->items[++queue->rear] = item;
}

// Function to dequeue (remove) an element from the queue
int dequeue(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow! Cannot dequeue from empty queue\n");
        return -1; // Return -1 indicating failure (assuming all queue elements are positive integers)
    }
    int dequeuedItem = queue->items[queue->front];
    if (queue->front == queue->rear) {
        // Reset queue to empty state
        queue->front = -1;
        queue->rear = -1;
    } else {
        queue->front++;
    }
    return dequeuedItem;
}

// Function to peek the front element of the queue (without removing it)
int peek(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. No elements to peek\n");
        return -1; // Return -1 indicating failure (assuming all queue elements are positive integers)
    }
    return queue->items[queue->front];
}

// Function to display the elements of the queue
void displayQueue(struct Queue *queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty. No elements to display\n");
        return;
    }
    printf("Queue elements: ");
    for (int i = queue->front; i <= queue->rear; ++i) {
        printf("%d ", queue->items[i]);
    }
    printf("\n");
}

int main() {
    struct Queue queue;
    initQueue(&queue); // Initialize the queue

    enqueue(&queue, 10);
    enqueue(&queue, 20);
    enqueue(&queue, 30);
    enqueue(&queue, 40);

    displayQueue(&queue);

    printf("Peek: %d\n", peek(&queue));

    printf("Dequeue: %d\n", dequeue(&queue));
    printf("Dequeue: %d\n", dequeue(&queue));

    displayQueue(&queue);

    return 0;
}
