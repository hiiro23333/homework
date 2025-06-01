#include <stdlib.h>   
#include <stdbool.h>  
#include <limits.h>
#include <math.h>     

// Q2. 子矩阵的最小绝对差
// 4 分
// 给你一个 m x n 的整数矩阵 grid 和一个整数 k。

// 对于矩阵 grid 中的每个连续的 k x k 子矩阵，计算其中任意两个 不同值 之间的 最小绝对差 。

// 返回一个大小为 (m - k + 1) x (n - k + 1) 的二维数组 ans，其中 ans[i][j] 表示以 grid 中坐标 (i, j) 为左上角的子矩阵的最小绝对差。

// 注意：如果子矩阵中的所有元素都相同，则答案为 0。

// 子矩阵 (x1, y1, x2, y2) 是一个由选择矩阵中所有满足 x1 <= x <= x2 且 y1 <= y <= y2 的单元格 matrix[x][y] 组成的矩阵

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** minAbsDiff(int** grid, int gridSize, int* gridColSize, int k, int* returnSize, int** returnColumnSizes) {
    int m = gridSize - k + 1;
    int n = gridColSize[0] - k + 1;
    *returnSize = m;
    *returnColumnSizes = (int*)malloc(m * sizeof(int));
    int **ans = (int**)malloc(m * sizeof(int*));

    for(int i = 0; i < m; i++) {
        (*returnColumnSizes)[i] = n;
        ans[i] = (int*)malloc(n * sizeof(int));
    }

    for(int i = 0; i < m; i++) {
        for(int j = 0; j < n; j++) {
            int values[k * k];
            int count = 0;

            for(int x = i; x < i + k; x++) {
                for(int y = j; y < j + k; y++) {
                    values[count++] = grid[x][y];
                }
            }

            int minDiff = INT_MAX;
            bool allSame = true;

            for(int a = 0; a < count; a++) {
                for(int b = a + 1; b < count; b++) {
                    if(values[a] != values[b]) {
                        allSame = false;
                        int diff = abs(values[a] - values[b]);
                        if(diff < minDiff) {
                            minDiff = diff;
                        }
                    }
                }
            }

            ans[i][j] = allSame ? 0 : minDiff;
        }
    }

    return ans;
}