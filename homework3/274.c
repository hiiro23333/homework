#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int cmp(const void *a, const void *b) {
    const int *num1 = (const int*)a;
    const int *num2 = (const int*)b;
    return *num1 - *num2;
}

int hIndex(int *citations, int citationsSize) {
    qsort(citations, citationsSize, sizeof(int), cmp);
    int h = 0, i = citationsSize - 1;
    while (i >= 0 && citations[i] > h) {
        h++;
        i--;
    }
    return h;
}