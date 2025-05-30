#include <stdlib.h>
#include <stdbool.h>

typedef struct LinkedNode {
    int value;
    struct LinkedNode *next;
    struct LinkedNode *prev;
} LinkedNode;

typedef struct {
    int size;
    int capacity;
    LinkedNode *front;
    LinkedNode *tail;
} MyCircularDeque;

LinkedNode* createNode(int value) {
    LinkedNode *node = (LinkedNode*)malloc(sizeof(LinkedNode));
    if (!node) {
        return NULL;
    }
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

MyCircularDeque* myCircularDequeCreate(int k) {
    MyCircularDeque *deque = (MyCircularDeque*)malloc(sizeof(MyCircularDeque));
    if (!deque) {
        return NULL;
    }
    deque->size = 0;
    deque->capacity = k;
    deque->front = createNode(-1);
    deque->tail = createNode(-1);
    deque->front->next = deque->tail;
    deque->tail->prev = deque->front;
    return deque;
}

bool myCircularDequeIsEmpty(MyCircularDeque* obj) {
    return obj->size == 0;
}

bool myCircularDequeIsFull(MyCircularDeque* obj) {
    return obj->size == obj->capacity;
}

bool myCircularDequeInsertFront(MyCircularDeque* obj, int value) {
    if (myCircularDequeIsFull(obj)) {
        return false;
    }
    LinkedNode *newNode = createNode(value);
    if (!newNode) {
        return false;
    }
    obj->front->next->prev = newNode;
    newNode->next = obj->front->next;
    newNode->prev = obj->front;
    obj->front->next = newNode;
    obj->size++;
    return true;
}

bool myCircularDequeInsertLast(MyCircularDeque* obj, int value) {
    if (myCircularDequeIsFull(obj)) {
        return false;
    }
    LinkedNode *newNode = createNode(value);
    if (!newNode) {
        return false;
    }
    obj->tail->prev->next = newNode;
    newNode->prev = obj->tail->prev;
    newNode->next = obj->tail;
    obj->tail->prev = newNode;
    obj->size++;
    return true;
}

bool myCircularDequeDeleteFront(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return false;
    }
    LinkedNode *temp = obj->front->next;
    obj->front->next = temp->next;
    temp->next->prev = obj->front;
    obj->size--;
    free(temp);
    return true;
}

bool myCircularDequeDeleteLast(MyCircularDeque* obj) {
    if (myCircularDequeIsEmpty(obj)) {
        return false;
    }
    LinkedNode *temp = obj->tail->prev;
    temp->prev->next = obj->tail;
    obj->tail->prev = temp->prev;
    obj->size--;
    free(temp);
    return true;
}

int myCircularDequeGetFront(MyCircularDeque* obj) {
    return myCircularDequeIsEmpty(obj) ? -1 : obj->front->next->value;
}

int myCircularDequeGetRear(MyCircularDeque* obj) {
    return myCircularDequeIsEmpty(obj) ? -1 : obj->tail->prev->value;
}

void myCircularDequeFree(MyCircularDeque* obj) {
    LinkedNode *cur = obj->front;
    while (cur) {
        LinkedNode *temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(obj);
}