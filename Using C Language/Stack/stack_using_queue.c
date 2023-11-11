#include <stdio.h>
#include <stdlib.h>

// Queue structure
struct Queue {
    int front, rear;
    unsigned capacity;
    int* array;
};

// Create a new queue with given capacity
struct Queue* createQueue(unsigned capacity) {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

// Function to check if a queue is empty
int isEmpty(struct Queue* queue) {
    return queue->front == -1;
}

// Function to enqueue an element to the queue
void enqueue(struct Queue* queue, int item) {
    if (isEmpty(queue))
        queue->front = 0;

    if (queue->rear == queue->capacity - 1) {
        printf("Queue overflow\n");
        return;
    }

    queue->array[++queue->rear] = item;
}

// Function to dequeue an element from the queue
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue underflow\n");
        return -1;
    }

    int item = queue->array[queue->front];
    queue->front++;

    if (queue->front > queue->rear)
        queue->front = queue->rear = -1;

    return item;
}

// Stack structure using two queues
struct Stack {
    struct Queue* queue1;
    struct Queue* queue2;
};

// Create a new stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->queue1 = createQueue(100);
    stack->queue2 = createQueue(100);
    return stack;
}

// Push an element onto the stack
void push(struct Stack* stack, int item) {
    enqueue(stack->queue1, item);

    while (!isEmpty(stack->queue2))
        enqueue(stack->queue1, dequeue(stack->queue2));

    struct Queue* temp = stack->queue1;
    stack->queue1 = stack->queue2;
    stack->queue2 = temp;
}

// Pop an element from the stack
int pop(struct Stack* stack) {
    if (isEmpty(stack->queue2)) {
        printf("Stack underflow\n");
        return -1;
    }

    return dequeue(stack->queue2);
}

// Get the top element of the stack
int top(struct Stack* stack) {
    if (isEmpty(stack->queue2)) {
        printf("Stack is empty\n");
        return -1;
    }

    return stack->queue2->array[stack->queue2->front];
}

// Driver program for testing
int main() {
    struct Stack* stack = createStack();

    int choice, data;

    while (1) {
        printf("\nStack Operations:\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Top\n");
        printf("4. Exit\n");

        printf("Enter your choice (1-4): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to push: ");
                scanf("%d", &data);
                push(stack, data);
                break;
            case 2:
                printf("Popped element: %d\n", pop(stack));
                break;
            case 3:
                printf("Top element: %d\n", top(stack));
                break;
            case 4:
                printf("Exiting the program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please enter a number between 1 and 4.\n");
        }
    }

    return 0;
}
