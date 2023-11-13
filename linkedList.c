#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Unable to allocate memory for new node\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// isEmpty() - checks if list is empty
bool isEmpty(Node* head) {
    if (head == NULL) {
        return true;
    } else {
        return false;
    }
}

// TODO: initializeList() - Sets up a new linked list, head point NULL
// Node* initializeList() {
//     // isn't this basically just Node* head = NULL?
//     Node* head = createNode(NULL);
//     return head;
// }

// insertAtBeginning() - inserts new node at start of list
Node* insertAtBeginning(Node* head, Node* newNode) {
    Node* ptr = head;
    newNode->next = ptr;
    return newNode;
}

// insertAtEnd() - inserts new node at end of list
Node* insertAtEnd(Node* head, Node* newNode) {
    Node* ptr = head;
    if (ptr == NULL) {
        return newNode;
    }
    while(ptr->next != NULL) {
        ptr = ptr->next->next;
    }
    ptr->next = newNode;
    return ptr;
}

// TODO: insertAfterNode() - inserts new node after given node
Node* insertAfterNode(Node* head, Node* node, Node* newNode) {
    Node* ptr = head;
    if (ptr == NULL) {
        return newNode;
    }
    while(ptr->next != NULL) {
        if (ptr->data == node->data) {
            newNode->next = ptr->next;
            ptr->next = newNode;
            break;
        }
        ptr = ptr->next->next;
    }
    return ptr;
}

// TODO: insertBeforeNode() - inserts new node before given node
Node* insertBeforeNode(Node* head, Node* node, Node* newNode) {
    // Check if the list is empty or if we are inserting before the first node
    if (head == NULL || head == node) {
        newNode->next = head;
        return newNode;
    }

    // Initialize two pointers for traversal
    Node* ptrL = head;
    Node* ptrR = head->next;

    // Traverse the list to find the node to insert before
    while (ptrR != NULL && ptrR != node) {
        ptrL = ptrR;
        ptrR = ptrR->next;
    }

    // If the node was found, insert the newNode before it
    if (ptrR == node) {
        ptrL->next = newNode;
        newNode->next = ptrR;
    } else {
        // If we reached the end of the list, the node to insert before wasn't found
        fprintf(stderr, "Node to insert before not found\n");
        exit(EXIT_FAILURE);
    }

    // Return the head of the list
    return head;
}

// TODO: deleteFromBeginning() - removes node from start of list

// TODO: deleteFromEnd() - removes node from end of list

// TODO: deleteNode() - removes specific node from list

// TODO: deleteList() - removes all nodes and frees memory

// TODO: findNode() - searches for node by value and returns 

// TODO: findWithCallback() - searchs for node using callback to compare

// TODO: traverseList() - goes through list start to end
void traverseList(Node* head) {
    Node* ptr = head;
    if (ptr == NULL) {
        printf("Empty list\n");
        exit(EXIT_SUCCESS);
    }
    while (ptr != NULL) {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
    printf("\n");
}
// TODO: listSize() - returns number of nodes in list

// TODO: reverseList() - reverse the order of nodes

// test our linked list implementation
int main() {
    Node* head = NULL;
    Node* node1 = createNode(1);
    head = insertAtBeginning(head, node1);
    traverseList(head);

    Node* node2 = createNode(2);
    head = insertAtEnd(head, node2);
    traverseList(head);

    Node* node3 = createNode(3);
    head = insertAfterNode(head, node1, node3);
    traverseList(head);

    Node* node4 = createNode(4);
    head = insertBeforeNode(head, node1, node4);
    traverseList(head);

    Node* node5 = createNode(5);
    head = insertBeforeNode(head, node3, node5);
    traverseList(head);
    // Add insertion logic here to link the new node into the list
    // Add traversal logic here to verfiy the list contents
    // Remember to free the allocated memory to avoid memory leaks
    return 0;
}