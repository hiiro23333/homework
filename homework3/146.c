#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DLinkedNode {
    int key;
    int value;
    struct DLinkedNode *next;
    struct DLinkedNode *prev;
} DLinkedNode;

typedef struct {
    int capacity;
    int size;
    DLinkedNode *head;
    DLinkedNode *tail;
    DLinkedNode **hash;
} LRUCache;

DLinkedNode* createNode(int key, int value) {
    DLinkedNode *node = (DLinkedNode*)malloc(sizeof(DLinkedNode));
    node->key = key;
    node->value = value;
    node->next = NULL;
    node->prev = NULL;
    return node;
}

LRUCache* lRUCacheCreate(int capacity) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacity = capacity;
    cache->size = 0;
    cache->head = createNode(-1, -1);
    cache->tail = createNode(-1, -1);
    cache->head->next = cache->tail;
    cache->tail->prev = cache->head;
    cache->hash = (DLinkedNode**)calloc(10001, sizeof(DLinkedNode*));
    return cache;
}

void removeNode(LRUCache *obj, DLinkedNode *node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
}

void addTohead(DLinkedNode *head, DLinkedNode *node) {
    node->next = head->next;
    node->prev = head;
    head->next->prev = node;
    head->next = node;
}

void moveTohead(LRUCache *obj, DLinkedNode *node) {
    removeNode(obj, node);
    addTohead(obj->head, node);
}

DLinkedNode* removeTail(LRUCache *obj) {
    DLinkedNode *node = obj->tail->prev;
    removeNode(obj, node);
    return node;
}

int lRUCacheGet(LRUCache* obj, int key) {
    if(obj->hash[key] == NULL) {
        return -1;
    }
    moveTohead(obj, obj->hash[key]);
    return obj->hash[key]->value;
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    if(obj->hash[key] != NULL) {
        moveTohead(obj, obj->hash[key]);
        obj->hash[key]->value = value;
        return;
    }
    DLinkedNode *newNode = createNode(key, value);
    obj->hash[key] = newNode;
    addTohead(obj->head, newNode);
    obj->size += 1; 
    if(obj->capacity < obj->size) {
        DLinkedNode* tail = removeTail(obj);
        obj->hash[tail->key] = NULL;
        free(tail);
        obj->size -= 1;
    }
}

void lRUCacheFree(LRUCache* obj) {
    DLinkedNode *cur = obj->head->next;
    while(cur != obj->tail) {
        DLinkedNode *temp = cur;
        cur = cur->next;
        free(temp);
    }
    free(obj->head);
    free(obj->tail);
    free(obj->hash);
    free(obj);
}