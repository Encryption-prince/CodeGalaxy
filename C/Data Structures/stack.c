#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Define a structure for the stack
struct Stack {
    int items[MAX_SIZE];
    int top;
};

// Function to initialize the stack
void initStack(struct Stack *stack) {
    stack->top = -1; // Initialize top of the stack to -1 (empty stack)
}

// Function to check if the stack is full
int isFull(struct Stack *stack) {
    return stack->top == MAX_SIZE - 1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack *stack, int item) {
    if (isFull(stack)) {
        printf("Stack overflow! Cannot push %d\n", item);
        return;
    }
    stack->items[++stack->top] = item;
}

// Function to pop (remove) an element from the stack
int pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow! Cannot pop from empty stack\n");
        return -1; // Return -1 indicating failure (assuming all stack elements are positive integers)
    }
    return stack->items[stack->top--];
}

// Function to peek the top element of the stack (without removing it)
int peek(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. No elements to peek\n");
        return -1; // Return -1 indicating failure (assuming all stack elements are positive integers)
    }
    return stack->items[stack->top];
}

// Function to display the elements of the stack
void displayStack(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack is empty. No elements to display\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = 0; i <= stack->top; ++i) {
        printf("%d ", stack->items[i]);
    }
    printf("\n");
}

int main() {
    struct Stack stack;
    initStack(&stack); // Initialize the stack

    push(&stack, 10);
    push(&stack, 20);
    push(&stack, 30);
    push(&stack, 40);

    displayStack(&stack);

    printf("Peek: %d\n", peek(&stack));

    printf("Pop: %d\n", pop(&stack));
    printf("Pop: %d\n", pop(&stack));

    displayStack(&stack);

    return 0;
}
