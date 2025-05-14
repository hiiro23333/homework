#include <stdio.h>
#include <stdlib.h>

int calculateMinimumTotal(int** triangle, int triangleSize, int* triangleColSize) {
    // 动态规划，二维数组用于存储每个元素的最小路径和
    int** dynamicProgrammingTable = (int**)malloc(sizeof(int*) * triangleSize);
    if (dynamicProgrammingTable == NULL) {
        return -1; // 内存分配失败处理
    }
    for (int i = 0; i < triangleSize; i++) {
        dynamicProgrammingTable[i] = (int*)malloc(sizeof(int) * triangleColSize[i]);
        if (dynamicProgrammingTable[i] == NULL) {
            // 释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(dynamicProgrammingTable[j]);
            }
            free(dynamicProgrammingTable);
            return -1; // 内存分配失败处理
        }
    }
    
    // 初始化动态规划数组的最后一行
    for (int i = 0; i < triangleColSize[triangleSize - 1]; i++) {
        dynamicProgrammingTable[triangleSize - 1][i] = triangle[triangleSize - 1][i];
    }
    
    // 从倒数第二行开始向上遍历
    for (int rowIndex = triangleSize - 2; rowIndex >= 0; rowIndex--) {
        for (int colIndex = 0; colIndex < triangleColSize[rowIndex]; colIndex++) {
            // 当前元素的最小路径和 = 当前元素的值 + 下一行相邻两个元素的最小路径和的较小值
            dynamicProgrammingTable[rowIndex][colIndex] = triangle[rowIndex][colIndex] + 
                (dynamicProgrammingTable[rowIndex + 1][colIndex] < dynamicProgrammingTable[rowIndex + 1][colIndex + 1] ? 
                 dynamicProgrammingTable[rowIndex + 1][colIndex] : dynamicProgrammingTable[rowIndex + 1][colIndex + 1]);
        }
    }
    
    // 返回顶部的最小路径和
    int result = dynamicProgrammingTable[0][0];
    
    // 释放内存
    for (int i = 0; i < triangleSize; i++) {
        free(dynamicProgrammingTable[i]);
    }
    free(dynamicProgrammingTable);
    
    return result;
}

// 测试代码
int main() {
    int triangleSize = 4;
    int triangleColSize[] = {1, 2, 3, 4};
    
    int triangle[4][4] = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };
    
    int** triangleArray = (int**)malloc(sizeof(int*) * triangleSize);
    if (triangleArray == NULL) {
        return 1; // 内存分配失败处理
    }
    for (int i = 0; i < triangleSize; i++) {
        triangleArray[i] = (int*)malloc(sizeof(int) * triangleColSize[i]);
        if (triangleArray[i] == NULL) {
            // 释放已分配的内存
            for (int j = 0; j < i; j++) {
                free(triangleArray[j]);
            }
            free(triangleArray);
            return 1; // 内存分配失败处理
        }
        for (int j = 0; j < triangleColSize[i]; j++) {
            triangleArray[i][j] = triangle[i][j];
        }
    }
    
    int result = calculateMinimumTotal(triangleArray, triangleSize, triangleColSize);
    if (result == -1) {
        printf("Memory allocation failed.\n");
        return 1;
    }
    printf("Minimum total path sum: %d\n", result);
    
    // 释放内存
    for (int i = 0; i < triangleSize; i++) {
        free(triangleArray[i]);
    }
    free(triangleArray);
    
    return 0;
}