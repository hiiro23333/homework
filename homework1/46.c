#include <stdio.h>
#include <stdlib.h>

// 用于存储所有排列结果
int** result;
int resultSize;

// 用于存储当前排列结果
int* currentPath;
int currentPathSize;

// 回溯法
void backtrace(int* nums, int numsSize) {
    if (currentPathSize == numsSize) {
        // 将当前排列添加到结果中
        int* temp = (int*)malloc(sizeof(int) * currentPathSize);
        if (temp == NULL) {
            return; // 内存分配失败处理
        }
        for (int i = 0; i < currentPathSize; i++) {
            temp[i] = currentPath[i];
        }
        result[resultSize] = temp;
        resultSize++;
        return;
    }

    for (int i = 0; i < numsSize; i++) {
        // 如果该位置已经被标记为已访问，则跳过
        if (nums[i] == -1) {
            continue;
        }
        // 将当前元素添加到排列中
        currentPath[currentPathSize++] = nums[i];
        // 标记当前元素为已访问
        int temp = nums[i];
        nums[i] = -1;
        backtrace(nums, numsSize);
        // 回溯
        nums[i] = temp;
        currentPathSize--;
    }
}

int** permute(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    result = (int**)malloc(sizeof(int*) * 10000); // 假设最多有10000种排列
    if (result == NULL) {
        return NULL; // 内存分配失败处理
    }
    currentPath = (int*)malloc(sizeof(int) * numsSize);
    if (currentPath == NULL) {
        free(result);
        return NULL; // 内存分配失败处理
    }
    resultSize = 0;
    currentPathSize = 0;
    backtrace(nums, numsSize);

    // 设置返回参数
    *returnSize = resultSize;
    *returnColumnSizes = (int*)malloc(sizeof(int) * resultSize);
    if (*returnColumnSizes == NULL) {
        for (int i = 0; i < resultSize; i++) {
            free(result[i]);
        }
        free(result);
        free(currentPath);
        return NULL; // 内存分配失败处理
    }
    for (int i = 0; i < resultSize; i++) {
        (*returnColumnSizes)[i] = numsSize;
    }

    return result;
}

// 测试
int main() {
    int nums[] = {1, 2, 3};
    int numsSize = 3;
    int returnSize;
    int* returnColumnSizes;
    int** result = permute(nums, numsSize, &returnSize, &returnColumnSizes);

    if (result == NULL) {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // 打印结果
    for (int i = 0; i < returnSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }

    // 释放内存
    for (int i = 0; i < returnSize; i++) {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}