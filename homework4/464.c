#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool canWin(int max, int total, int used, int* memo) {
    if (memo[used] != -1) {
        return memo[used];
    }
    
    for (int i = 1; i <= max; i++) {
        int mask = 1 << (i - 1);
        if ((used & mask) == 0) {  // 数字i未被使用
            if (total <= i || !canWin(max, total - i, used | mask, memo)) {
                memo[used] = true;
                return true;
            }
        }
    }
    
    memo[used] = false;
    return false;
}

bool canIWin(int maxChoosableInteger, int desiredTotal) {
    // 初始检查
    if (desiredTotal <= 0) {
        return true;
    }
    
    int sum = maxChoosableInteger * (maxChoosableInteger + 1) / 2;
    if (sum < desiredTotal) {
        return false;
    }
    
    // 初始化记忆化数组
    int memoSize = 1 << maxChoosableInteger;
    int* memo = (int*)malloc(memoSize * sizeof(int));
    memset(memo, -1, memoSize * sizeof(int));
    
    bool result = canWin(maxChoosableInteger, desiredTotal, 0, memo);
    
    free(memo);
    return result;
}