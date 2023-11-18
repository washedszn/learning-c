#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    int priority;
    struct Node* next;
} Node;

typedef struct PriorityQueue {
    Node* front;
    Node* back;
    int size;
    int capacity;
} PriorityQueue;

Node* createNode(int data, int priority) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Cannot allocate memory for node");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->priority = priority;
    node->next = NULL;
    return node;
}

PriorityQueue* createPriorityQueue(int capacity) {
    PriorityQueue* queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (queue == NULL) {
        fprintf(stderr, "Cannot allocate memory to priority queue");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->back = NULL;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

PriorityQueue* enqueue(PriorityQueue* queue, Node* node) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return queue;
    }
    Node* front = queue->front;
    Node* back = queue->back;
    if (queue->size == 0) {
        queue->front = node;
        queue->back = node;
        queue->size++;
    } else if (queue->size == queue->capacity) {
        fprintf(stderr, "Queue is full");
    } else if (front->priority < node->priority) {
        node->next = front;
        queue->front = node;
        queue->size++;
    } else {
        // find next priority using L/R pointers
        Node* ptrL = front;
        Node* ptrR = front->next;

        while (ptrR != NULL && ptrR->priority >= node->priority) {
            ptrL = ptrR;
            ptrR = ptrR->next;
        }

        if (ptrR != NULL) {
            ptrL->next = node;
            node->next = ptrR;
        } else {
            queue->back->next = node;
            queue->back = node;
        }
        queue->size++;
    }
    return queue;
}

PriorityQueue* dequeue(PriorityQueue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return queue;
    }
    Node* front = queue->front;
    queue->front = front->next;
    free(front);
    queue->size--;
    return queue;
}

Node* peek(PriorityQueue* queue) {
    return queue->front;
}

bool isFull(PriorityQueue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return false;
    }
    if (queue->size == queue->capacity) {
        return true;
    }
    return false;
}

bool isEmpty(PriorityQueue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return false;
    }
    if (queue->size == 0) {
        return true;
    }
    return false;
}

void clearQueue(PriorityQueue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return;
    }
    Node* current = queue->front;
    Node* next = current->next;
    while (current != NULL && current != queue->back) {
        next = current->next;
        free(current);
        current = next;
    }
    free(queue->back);
    queue->front = NULL;
    queue->back = NULL;
    queue->size = 0;
}

int main() {
    PriorityQueue* queue = createPriorityQueue(6);

    Node* node1 = createNode(1, 2);
    Node* node2 = createNode(2, 2);
    Node* node3 = createNode(3, 3);
    Node* node4 = createNode(4, 2);
    Node* node5 = createNode(5, 5);
    Node* node6 = createNode(6, 1);

    enqueue(queue, node1);
    enqueue(queue, node2);
    enqueue(queue, node3);
    enqueue(queue, node4);
    enqueue(queue, node5);
    enqueue(queue, node6);
    dequeue(queue);

    clearQueue(queue);

    if (isEmpty(queue)) {
        printf("yes");
    }

    return 0;
}