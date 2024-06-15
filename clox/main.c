#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
    struct Node *prev;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
} LinkedList;

void init(LinkedList *list) {
    list->head = NULL;
    list->tail = NULL;
}

void add(LinkedList *list, int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
}

void find(LinkedList *list, int data, Node **node) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->data == data) {
            *node = current;
            return;
        }
        current = current->next;
    }
    *node = NULL;
}

void delete(LinkedList *list, int data) {
    Node *node;
    find(list, data, &node);
    if (node == NULL) {
        return;
    }

    if (node->prev == NULL) {
        list->head = node->next;
    } else {
        node->prev->next = node->next;
    }

    if (node->next == NULL) {
        list->tail = node->prev;
    } else {
        node->next->prev = node->prev;
    }

    free(node);
}

void ls_free(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }
}


int main(void) {
    LinkedList list;
    init(&list);
    for (int i = 0; i < 10; i++) {
        add(&list, i);
    }
    Node *seven;
    find(&list, 7, &seven);
    if (seven != NULL) {
        printf("Found: %d\n", seven->data);
    } else {
        printf("Not found\n");
    }
    delete(&list, 7);

    for (Node *current = list.head; current != NULL; current = current->next) {
        printf("%d\n", current->data);
    }
    ls_free(&list);

    return 0;
}
