#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* back;
} Queue;

// create node
Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Failed to allocate memory for node");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

// create queue
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue == NULL) {
        fprintf(stderr, "Failed to allocate memory for queue");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->back = NULL;
    return queue;
}

// enqueue
Queue* enqueue(Queue* queue, Node* node) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return queue;
    }
    if (queue->front == NULL) {
        queue->front = node;
        queue->back = node;
    } else {
        queue->back->next = node;
        queue->back = node;
    }
    return queue;
}

// dequeue
Queue* dequeue(Queue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return NULL;
    }
    Node* front = queue->front;
    Node* back = queue->back;
    if (front == NULL) {
        fprintf(stderr, "Nothing to dequeue");
    } else if (front == back) {
        queue->front = NULL;
        queue->back = NULL;
        free(front);
    } else {
        queue->front = front->next;
        free(front);
    }
    return queue;
}

// Peek
Node* peek(Queue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return NULL;
    }
    return queue->front;
}

// isEmpty
bool isEmpty(Queue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return false;
    }
    if (queue->front == NULL) {
        return true;
    }
    return false;
}

int main() {
    Queue* queue = createQueue();

    Node* node1 = createNode(1);
    Node* node2 = createNode(2);
    Node* node3 = createNode(3);
    Node* node4 = createNode(4);
    Node* node5 = createNode(5);

    queue = enqueue(queue, node1);
    queue = enqueue(queue, node2);
    queue = enqueue(queue, node3);
    queue = dequeue(queue);
    enqueue(queue, node4);
    dequeue(queue);
    enqueue(queue, node5);

    if (isEmpty(queue)) {
        printf("yes");
    } else {
        printf("no");
    }

    return 0;
}