#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

typedef struct PopResult {
    int value;
    int status;
} PopResult;

// implementa create node
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Error allocating memory for node");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

// implement createStack
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if (stack == NULL) {
        fprintf(stderr, "Error allocating memory for stack");
        exit(EXIT_FAILURE);
    }
    stack->top = NULL;
    return stack;
}

// implement push 
Stack* push(Stack* stack, Node* node) {
    if (stack->top == NULL) {
        stack->top = node;
        return stack;
    }
    Node* temp = stack->top;
    node->next = temp;
    stack->top = node;
    return stack;
}

// implement pop
PopResult pop(Stack* stack) {
    PopResult result;
    if (stack->top == NULL) {
        fprintf(stderr, "stack is empty");
        result.status = -1;
        return result; // sentinel value indicating the stack is empty
    }
    Node* temp = stack->top;
    result.value = stack->top->data;
    stack->top = temp->next;
    free(temp);
    result.status = 0;
    return result;
}

// implement peek
Node* peek(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Stack is null");
        return NULL;
    }
    return stack->top;
}

// implement isEmpty
bool isEmpty(Stack* stack) {
    if (stack == NULL) {
        fprintf(stderr, "Stack is NULL");
        return NULL;
    }
    if (stack->top == NULL) {
        printf("Stack is empty");
        return true;
    }
    return false;
}

int main() {
    Stack* stack = createStack();

    Node* node1 = createNode(1);

    stack = push(stack, node1);

    Node* node2 = createNode(2);

    stack = push(stack, node2);

    PopResult result = pop(stack);
    if (result.status == 0) { 
        printf("yes");
    }
    isEmpty(stack);

    return 0;
}