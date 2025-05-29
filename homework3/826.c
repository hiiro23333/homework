#include <stdlib.h>

typedef struct {
    int key;
    int value;
} Pair;

int compare(const void *a, const void *b) {
    const Pair *pairA = (const Pair *)a;
    const Pair *pairB = (const Pair *)b;
    return pairA->key - pairB->key;
}

// 贪心思想：找到每个工人能完成的、且报酬最多的那一份工作
int maxProfitAssignment(int* difficulty, int difficultySize, int* profit, int profitSize, int* worker, int workerSize) {
    int res = 0;
    Pair *works = (Pair*)malloc(sizeof(Pair) * difficultySize);
    if (works == NULL) {
        return 0; // 内存分配失败
    }
    
    for (int i = 0; i < difficultySize; i++) {
        works[i].key = difficulty[i];
        works[i].value = profit[i]; 
    }
    
    qsort(works, difficultySize, sizeof(Pair), compare);
    
    for (int i = 0; i < workerSize; i++) {
        int job = 0;
        for (int j = 0; j < difficultySize; j++) {
            if (works[j].key > worker[i]) {
                break;
            }
            job = (works[j].value > job) ? works[j].value : job;
        }
        res += job;
    }
    
    free(works);
    return res;
}