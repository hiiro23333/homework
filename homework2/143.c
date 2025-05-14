#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构体
typedef struct ListNode
{
    int val;
    struct ListNode *next;
} ListNode;

// 创建新节点
ListNode* CreateListNode(int val)
{
    ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
    if (newNode == NULL) {
        return NULL; // 内存分配失败处理
    }
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// 找到链表的中点
ListNode* FindMiddleNode(ListNode *head)
{
    if (head == NULL || head->next == NULL) {
        return head; // 处理空链表或单节点链表
    }
    ListNode *slow = head;
    ListNode *fast = head->next;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// 反转链表
ListNode* ReverseList(ListNode *head)
{
    ListNode *prev = NULL;
    ListNode *curr = head;
    while (curr) {
        ListNode *nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}

// 合并两个链表
void MergeTwoLists(ListNode *firstList, ListNode *secondList)
{
    if (firstList == NULL || secondList == NULL) {
        return;
    }
    while (secondList) {
        ListNode *next1 = firstList->next;
        ListNode *next2 = secondList->next;
        firstList->next = secondList;
        secondList->next = next1;
        firstList = next1;
        secondList = next2;
    }
    return;
}

// 重排链表
void ReorderList(ListNode *head)
{
    if (!head || !head->next || !head->next->next) {
        return;
    }
    // 找到链表中点
    ListNode *mid = FindMiddleNode(head);
    // 反转后半部分链表
    ListNode *head2 = ReverseList(mid->next);
    mid->next = NULL;
    // 合并两个链表
    MergeTwoLists(head, head2);
    return;
}

// 释放链表内存
void FreeListNode(ListNode *head)
{
    ListNode *curr = head;
    while (curr) {
        ListNode* next = curr->next;
        free(curr);
        curr = next;
    }
    return;
}

// 测试代码
int main()
{
    // 创建测试链表
    ListNode *head = CreateListNode(1);
    head->next = CreateListNode(2);
    head->next->next = CreateListNode(3);
    head->next->next->next = CreateListNode(4);
    head->next->next->next->next = CreateListNode(5);
    // 重排链表
    ReorderList(head);
    // 打印结果
    ListNode *curr = head;
    while (curr) {
        printf("%d ", curr->val);
        curr = curr->next;
    }
    printf("\n");
    // 释放内存
    FreeListNode(head);
    return 0;
}