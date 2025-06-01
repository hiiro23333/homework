#include <stdbool.h>

// Q1. 等积子集的划分方案
// 4 分
// 给你一个整数数组 nums，其中包含的正整数 互不相同 ，另给你一个整数 target。

// 请判断是否可以将 nums 分成两个 非空、互不相交 的 子集 ，并且每个元素必须  恰好 属于 一个 子集，使得这两个子集中元素的乘积都等于 target。

// 如果存在这样的划分，返回 true；否则，返回 false。

// 子集 是数组中元素的一个选择集合。

bool fun(int* nums, int numsSize,long long target,long long prodA, long long prodB, int index){
    if(index == numsSize){
        return prodA == target && prodB == target;
    }

    if(prodA * nums[index] <= target && fun(nums,numsSize,target,prodA * nums[index],prodB,index + 1)){
        return true;
    }

    if(prodB * nums[index] <= target && fun(nums,numsSize,target,prodA,prodB * nums[index],index + 1)){
        return true;
    }

    return false;
}


bool checkEqualPartitions(int* nums, int numsSize, long long target) {
    if(target == 0){
        for(int i = 0;i < numsSize;i++){
            if(nums[i] != 0){
                return false;
            }
        }
        return true;
    }

    return fun(nums,numsSize,target,1,1,0);
}