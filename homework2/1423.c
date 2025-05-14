#include <stdio.h>
#include <stdlib.h>

// 计算最大分数:滑动窗口，找到数组中长度为 cardPointsSize - k 的子数组的最小和，与数组总和相减就是能拿到的最大分数
int CalculateMaxScore(int *cardPoints, int cardPointsSize, int k)
{
    if (cardPoints == NULL || cardPointsSize <= 0 || k < 0 || k > cardPointsSize) {
        return -1; // 参数无效处理
    }
    int totalSum = 0;
    for (int i = 0; i < cardPointsSize; i++) {
        totalSum += cardPoints[i];
    }
    int windowSize = cardPointsSize - k;
    int windowSum = 0;
    for (int i = 0; i < windowSize; i++) {
        windowSum += cardPoints[i];
    }
    // 找到长度为 cardPointsSize - k 的子数组的最小和
    int minWindowSum = windowSum;
    for (int i = windowSize; i < cardPointsSize; i++) {
        windowSum += cardPoints[i] - cardPoints[i - windowSize];
        if (windowSum < minWindowSum) {
            minWindowSum = windowSum;
        }
    }
    return totalSum - minWindowSum;
}

// 测试代码
int main()
{
    int cardPoints[] = {1, 2, 3, 4, 5};
    int cardPointsSize = 5;
    int k = 3;
    int result = CalculateMaxScore(cardPoints, cardPointsSize, k);
    printf("Maximum score: %d\n", result);
    return 0;
}