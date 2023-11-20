#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int ac = *(int *)a;
    int bc = *(int *)b;
    return ac < bc;
}

int hIndex(int* citations, int citationsSize) {
    qsort(citations, citationsSize, sizeof(int), compare);
    int h = 0;
    for (int i = 0; i < citationsSize; i++) {
        if(citations[i] >= i+1) {
            h = i+1;
        }
    } 
    return h;   
}

int a[] = {1,3,1};

int main()
{
    printf("hindex:%d.\n", hIndex(a, sizeof(a)/sizeof(int)));
}
