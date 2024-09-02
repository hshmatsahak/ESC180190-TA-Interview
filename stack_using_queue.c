#include <stdio.h>
#include <stdlib.h>

// Define a Queue structure
typedef struct Queue {
    int front, rear, size;
    unsigned capacity;
    int* array;
} Queue;

// Function to create a queue
Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

// Queue is full when size becomes equal to the capacity
int isFull(Queue* queue) {
    return (queue->size == queue->capacity);
}

// Queue is empty when size is 0
int isEmpty(Queue* queue) {
    return (queue->size == 0);
}

// Function to add an item to the queue
void enqueue(Queue* queue, int item) {
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

// Function to remove an item from the queue
int dequeue(Queue* queue) {
    if (isEmpty(queue))
        return -1;
    int item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

// Function to get the front of the queue
int front(Queue* queue) {
    if (isEmpty(queue))
        return -1;
    return queue->array[queue->front];
}

// Stack structure using two queues
typedef struct Stack {
    Queue *q1, *q2;
} Stack;

// Function to create a stack
Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->q1 = createQueue(capacity);
    stack->q2 = createQueue(capacity);
    return stack;
}

// Push operation
void push(Stack* stack, int x) {
    enqueue(stack->q2, x);
    while (!isEmpty(stack->q1)) {
        enqueue(stack->q2, dequeue(stack->q1));
    }
    Queue* temp = stack->q1;
    stack->q1 = stack->q2;
    stack->q2 = temp;
}

// Pop operation
int pop(Stack* stack) {
    if (isEmpty(stack->q1))
        return -1;
    return dequeue(stack->q1);
}

// Peek operation
int top(Stack* stack) {
    if (isEmpty(stack->q1))
        return -1;
    return front(stack->q1);
}

// Check if the stack is empty
int isStackEmpty(Stack* stack) {
    return isEmpty(stack->q1);
}

int main() {
    Stack* stack = createStack(100);
    
    push(stack, 10);
    push(stack, 20);
    push(stack, 30);
    
    printf("Top element: %d\n", top(stack)); // 30
    printf("Popped element: %d\n", pop(stack)); // 30
    printf("Top element: %d\n", top(stack)); // 20
    printf("Is stack empty? %s\n", isStackEmpty(stack) ? "Yes" : "No"); // No

    return 0;
}
