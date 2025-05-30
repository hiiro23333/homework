#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

typedef struct {
    int value;
    int count;// 出现次数
    UT_hash_handle hh;
} HashItem;

HashItem* find_in_hash(HashItem* hashTable, int key) {
    HashItem* result = NULL;
    HASH_FIND_INT(hashTable, &key, result);
    return result;
}

int findPairs(int* nums, int numsSize, int k) {
    if (k < 0) return 0;  // k不能为负数
    
    HashItem* visited = NULL;
    HashItem* item = NULL;

    // 构建哈希表，统计每个数出现的次数
    for (int i = 0; i < numsSize; i++) {
        int num = nums[i];
        item = find_in_hash(visited, num);
        if (item == NULL) {
            item = (HashItem*)malloc(sizeof(HashItem));
            item->value = num;
            item->count = 1;
            HASH_ADD_INT(visited, value, item);
        } else {
            item->count++;
        }
    }

    int res = 0;

    // 遍历哈希表寻找满足条件的数对
    for (item = visited; item != NULL; item = item->hh.next) {
        if (k == 0) {
            // 处理k=0的特殊情况，要求同一个数出现至少两次
            if (item->count >= 2) {
                res++;
            }
        } else {
            // 检查是否存在value + k的数
            int target = item->value + k;
            HashItem* temp = find_in_hash(visited, target);
            if (temp != NULL) {
                res++;
            }
        }
    }

    // 释放哈希表内存
    HashItem* current_item;
    HashItem* next_item;
    HASH_ITER(hh, visited, current_item, next_item) {
        HASH_DEL(visited, current_item);
        free(current_item);
    }

    return res;
}