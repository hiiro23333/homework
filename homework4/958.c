#include <stdbool.h>
#include <stdlib.h>

// 二叉树节点定义
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

// 队列结构定义
typedef struct {
    struct TreeNode** data;
    int front;
    int rear;
    int capacity;
} Queue;

Queue* createQueue(int capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->data = (struct TreeNode**)malloc(capacity * sizeof(struct TreeNode*));
    queue->front = 0;
    queue->rear = 0;
    queue->capacity = capacity;
    return queue;
}

bool isEmpty(Queue* queue) {
    return queue->front == queue->rear;
}

void enqueue(Queue* queue, struct TreeNode* node) {
    if (queue->rear == queue->capacity) {
        return;
    }
    queue->data[queue->rear++] = node;
}

struct TreeNode* dequeue(Queue* queue) {
    if (isEmpty(queue)) {
        return NULL;
    }
    return queue->data[queue->front++];
}

void freeQueue(Queue* queue) {
    free(queue->data);
    free(queue);
}

bool isCompleteTree(struct TreeNode* root) {
    if (root == NULL) {
        return true;
    }
    
    Queue* queue = createQueue(1000); // 假设节点数不超过1000
    enqueue(queue, root);
    
    bool hasNull = false;
    
    while (!isEmpty(queue)) {
        struct TreeNode* node = dequeue(queue);
        
        if (node == NULL) {
            hasNull = true;
        } else {
            // 如果之前已经出现过空节点，现在又遇到非空节点，则不是完全二叉树
            if (hasNull) {
                freeQueue(queue);
                return false;
            }      
            // 将左右孩子加入队列，无论是否为NULL
            enqueue(queue, node->left);
            enqueue(queue, node->right);
        }
    }
    
    freeQueue(queue);
    return true;
}