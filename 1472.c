#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义链表节点结构体
typedef struct Node
{
    char *url;
    struct Node *next;
    struct Node *prev;
} Node;

// 定义浏览器历史记录结构体
typedef struct
{
    Node *current;
} BrowserHistory;

// 创建新节点
Node* CreateNode(char *url)
{
    if (url == NULL) {
        return NULL; // 入参检查
    }
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL; // 内存分配失败处理
    }
    newNode->url = strdup(url);
    if (newNode->url == NULL) {
        free(newNode);
        return NULL; // 内存分配失败处理
    }
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// 创建浏览器历史记录
BrowserHistory* CreateBrowserHistory(char *homepage)
{
    if (homepage == NULL) {
        return NULL; // 入参检查
    }
    BrowserHistory *history = (BrowserHistory*)malloc(sizeof(BrowserHistory));
    if (history == NULL) {
        return NULL; // 内存分配失败处理
    }
    history->current = CreateNode(homepage);
    if (history->current == NULL) {
        free(history);
        return NULL; // 内存分配失败处理
    }
    return history;
}

// 访问新页面
void VisitPage(BrowserHistory *obj, char *url)
{
    if (obj == NULL || url == NULL) {
        return; // 入参检查
    }
    Node *newNode = CreateNode(url);
    if (newNode == NULL) {
        return; // 内存分配失败处理
    }
    obj->current->next = newNode;
    newNode->prev = obj->current;
    obj->current = newNode;
}

// 后退 steps 步
char* GoBack(BrowserHistory *obj, int steps)
{
    if (obj == NULL || steps < 0) {
        return NULL; // 入参检查
    }
    while (steps > 0 && obj->current->prev) {
        obj->current = obj->current->prev;
        steps--;
    }
    return obj->current->url;
}

// 前进 steps 步
char* GoForward(BrowserHistory *obj, int steps)
{
    if (obj == NULL || steps < 0) {
        return NULL; // 入参检查
    }
    while (steps > 0 && obj->current->next) {
        obj->current = obj->current->next;
        steps--;
    }
    return obj->current->url;
}

// 释放内存
void FreeBrowserHistory(BrowserHistory *obj)
{
    if (obj == NULL) {
        return; // 入参检查
    }
    Node *curr = obj->current;
    while (curr) {
        Node *next = curr->next;
        free(curr->url);
        free(curr);
        curr = next;
    }
    free(obj);
}

// 测试代码
int main()
{
    BrowserHistory *browser = CreateBrowserHistory("leetcode.com");
    if (browser == NULL) {
        printf("Failed to create browser history.\n");
        return 1;
    }
    VisitPage(browser, "google.com");
    VisitPage(browser, "facebook.com");
    VisitPage(browser, "youtube.com");
    printf("Current URL after visiting: %s\n", browser->current->url); // 输出 "youtube.com"
    printf("After back 1 step: %s\n", GoBack(browser, 1)); // 输出 "facebook.com"
    printf("After back 1 step: %s\n", GoBack(browser, 1)); // 输出 "google.com"
    printf("After forward 1 step: %s\n", GoForward(browser, 1)); // 输出 "facebook.com"
    FreeBrowserHistory(browser);

    return 0;
}