#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct CircularQueue {
    Node* front;
    Node* back;
    int size;
    int capacity;
} CircularQueue;

Node* createNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    if (node == NULL) {
        fprintf(stderr, "Unable to allocate memory to node");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}

CircularQueue* createCircularQueue(int capacity) {
    CircularQueue* queue = (CircularQueue*)malloc(sizeof(CircularQueue));
    if (queue == NULL) {
        fprintf(stderr, "Unable to allocate memory to CircularQueue");
        exit(EXIT_FAILURE);
    }
    queue->front = NULL;
    queue->back = NULL;
    queue->size = 0;
    queue->capacity = capacity;
    return queue;
}

CircularQueue* enqueue(CircularQueue* queue, Node* node) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
    } else if (queue->size == queue->capacity) {
        printf("Unable to enqueue, queue is at capacity");
    } else if (queue->front == NULL) {
        queue->front = node;
        queue->back = node;
        queue->size++;
    } else {
        // add the new node to queue
        queue->back->next = node;
        queue->back = node;
        // link the front and back of queue
        queue->back->next = queue->front;
        queue->size++;
    }
    return queue;
}

CircularQueue* dequeue(CircularQueue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return queue;
    }
    Node* front = queue->front;
    Node* back = queue->back;
    if (queue->size == 0) {
        printf("Queue is empty");
    } else if (front == back) {
        queue->front = NULL;
        queue->back = NULL;
        free(back);
        queue->size--;
    } else {
        queue->front = front->next;
        free(front);
        back->next = queue->front;
        queue->size--;
    }
    return queue;
}

Node* peek(CircularQueue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return NULL;
    }
    return queue->front;
}

bool isFull(CircularQueue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return false;
    }
    if (queue->size == queue->capacity) {
        return true;
    }
    return false;
}

bool isEmpty(CircularQueue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return false;
    }
    if (queue->size == 0) {
        return true;
    }
    return false;
}

void clearQueue(CircularQueue* queue) {
    if (queue == NULL) {
        fprintf(stderr, "Queue is NULL");
        return;
    }

    Node* current = queue->front;
    Node* next;

    while (current != NULL && current != queue->back) {
        next = current->next;
        free(current);
        current = next;
    }

    // freeing the last node
    free(queue->back);

    queue->front = NULL;
    queue->back = NULL;
    queue->size = 0;
}

int main() {
    Node* node1 = createNode(1);
    Node* node2 = createNode(2);
    Node* node3 = createNode(3);
    Node* node4 = createNode(4);

    CircularQueue* queue = createCircularQueue(3);

    enqueue(queue, node1);
    enqueue(queue, node2);
    enqueue(queue, node3);
    enqueue(queue, node4);

    clearQueue(queue);    

    return 0;
}