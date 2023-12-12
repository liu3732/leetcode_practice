#include <stdio.h>
#include <stdlib.h>

typedef enum {
    INIT,
    MERGING,
    MERGED
} enum_t;

void add(int ***out, int l, int r, int *inOutSize)
{
    *out = (int **)realloc(*out, sizeof(int *) * (*inOutSize + 1));
    (*out)[*inOutSize] = (int *)malloc(sizeof(int) * 2);
    (*out)[*inOutSize][0] = l;
    (*out)[*inOutSize][1] = r;
    (*inOutSize)++;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** insert(int** intervals, int intervalsSize, int* intervalsColSize, int* newInterval, int newIntervalSize, int* returnSize, int** returnColumnSizes) {
    int **ret = NULL;

    int l;
    int r;
    *returnSize = 0;
    enum_t state = INIT;
    for (int i=0; i < intervalsSize; i++) {
        switch(state) {
            case(INIT):
                if (intervals[i][1] < newInterval[0]) {
                    add(&ret, intervals[i][0], intervals[i][1], returnSize);
                } else if (intervals[i][0] > newInterval[1]) {
                    add(&ret, newInterval[0], newInterval[1], returnSize);
                    add(&ret, intervals[i][0], intervals[i][1], returnSize);
                    state = MERGED;
                } else {
                    l = min(intervals[i][0], newInterval[0]);
                    r = max(intervals[i][1], newInterval[1]);
                    state = MERGING;
                }
                break;
            case(MERGING):
                if (r < intervals[i][0]) {
                    add(&ret, l, r, returnSize);
                    add(&ret, intervals[i][0], intervals[i][1], returnSize);
                    state = MERGED;
                } else {
                    r = max(r, intervals[i][1]);
                    state = MERGING;
                }
                break;
            case(MERGED):
                add(&ret, intervals[i][0], intervals[i][1], returnSize);
                break;
        }
    }

    // last handling.
    if (state == MERGING) {
        add(&ret, l, r, returnSize);
        state = MERGED;
    } else if (state == INIT)
    {
        add(&ret, newInterval[0], newInterval[1], returnSize);
        state = MERGED;
    }
    

    *returnColumnSizes = (int *)malloc(*returnSize * sizeof(int));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }
    return ret;
}

#define NELEM 2
int g_intervals[][NELEM] = {
    {1, 5}
};

int g_new[] = {
    2, 7
};

int main()
{
    int intervalSize = sizeof(g_intervals)/sizeof(g_intervals[0]);
    int **t = (int **)malloc(sizeof(g_intervals));
    for (int i = 0; i < intervalSize; i++) {
        t[i] = (int *)malloc(2 * sizeof(int));
        t[i][0] = g_intervals[i][0];
        t[i][1] = g_intervals[i][1];
    }

    int intervalColSize = 2;
    int retSize = 0;
    int *retColSizes = NULL;
    int **ret = insert(t, intervalSize, &intervalColSize, g_new, 2, &retSize, &retColSizes);

    for (int i = 0; i < retSize; i++) {
        printf("[%d, %d]\n", ret[i][0], ret[i][1]);
        free(ret[i]);
    }
    free(ret);
    free(retColSizes);

    for (int i = 0; i < intervalSize; i++) {
        free(t[i]);
    }  
    free(t);
}