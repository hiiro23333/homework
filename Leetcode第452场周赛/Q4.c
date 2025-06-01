

// Q4. 分割数组后不同质数的最大数目
// 困难
// 7 分
// 给你一个长度为 'n' 的整数数组 nums，以及一个二维整数数组 queries，其中 queries[i] = [idx, val]。

// 对于每个查询：

// 1.更新 nums[idx] = val。
// 2.选择一个满足 1 <= k < n 的整数 k ，将数组分为非空前缀 nums[0..k-1] 和后缀 nums[k..n-1]，使得每部分中 不同 质数的数量之和 最大 。
// 注意：每次查询对数组的更改将持续到后续的查询中。

// 返回一个数组，包含每个查询的结果，按给定的顺序排列。

// 质数是大于 1 的自然数，只有 1 和它本身两个因数。

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* maximumCount(int* nums, int numsSize, int** queries, int queriesSize, int* queriesColSize, int* returnSize) {
    //没时间写了
}