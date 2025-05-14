#include <stdio.h>
#include <string.h>
#include <stdbool.h>

bool checkIfPangram(const char *sentence) {
    // 创建一个大小为26的数组，用于记录每个字母是否出现过
    int letters[26] = {0};
    
    for (int index = 0; sentence[index] != '\0'; index++) {
        char currentChar = sentence[index];
        letters[currentChar - 'a']++;
    }
    
    // 检查所有字母是否都出现过
    for (int i = 0; i < 26; i++) {
        if (letters[i] == 0) {
            return false;
        }
    }
    
    return true;
}

int main() {
    const char *sentence1 = "thequickbrownfoxjumpsoverthelazydog";
    const char *sentence2 = "leetcode";
    
    printf("Test 1: %s\n", checkIfPangram(sentence1) ? "true" : "false");
    printf("Test 2: %s\n", checkIfPangram(sentence2) ? "true" : "false");
    
    return 0;
}