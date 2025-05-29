#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

bool checkInclusion(char* s1, char* s2) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    
    if (len1 > len2) return false;
    
    int count1[26] = {0};  // s1的字符频率
    int count2[26] = {0};  // 滑动窗口的字符频率
    
    // 统计s1的字符频率
    for (int i = 0; i < len1; i++) {
        count1[s1[i] - 'a']++;
    }
    
    // 初始化滑动窗口
    for (int i = 0; i < len1; i++) {
        count2[s2[i] - 'a']++;
    }
    
    // 比较初始窗口
    bool match = true;
    for (int i = 0; i < 26; i++) {
        if (count1[i] != count2[i]) {
            match = false;
            break;
        }
    }
    if (match) return true;
    
    // 滑动窗口
    for (int i = len1; i < len2; i++) {
        // 移除左边界的字符
        count2[s2[i - len1] - 'a']--;
        // 添加右边界的字符
        count2[s2[i] - 'a']++;   
        // 检查是否匹配
        match = true;
        for (int j = 0; j < 26; j++) {
            if (count1[j] != count2[j]) {
                match = false;
                break;
            }
        }
        if (match) return true;
    }
    
    return false;
}