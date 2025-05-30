#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

// 合并两个有序链表
struct ListNode* mergeTwoLists(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode dummy;
    struct ListNode* tail = &dummy;
    dummy.next = NULL;

    while (l1 && l2) {
        if (l1->val <= l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    // 如果其中一个链表还有剩余节点，直接连接到结果链表的末尾
    if (l1) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    return dummy.next;
}

// 递归
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0) return NULL;
    if (listsSize == 1) return lists[0];

    int mid = listsSize / 2;
    struct ListNode** left = lists;
    struct ListNode** right = lists + mid;

    return mergeTwoLists(mergeKLists(left, mid), mergeKLists(right, listsSize - mid));
}