#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int compare(const void *a, const void *b)
{
    int *ca = *(int **)a;
    int *cb = *(int **)b;
    if (ca[0] > cb[0]) {
        return 1;
    } else if (ca[0] == cb[0])
    {
        if (ca[1] == cb[1]) {
            return 0;
        } else if (ca[1] > cb[1])
        {
            return 1;
        } else {
            return -1;
        }
    } else {
        return -1;
    }
    
}

void add(int ***out, int idx, int l, int r)
{
    *out = (int **)realloc(*out, sizeof(int *) * (idx + 1));
    (*out)[idx] = (int *)malloc(sizeof(int) * 2);
    (*out)[idx][0] = l;
    (*out)[idx][1] = r;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {

    int i = 0;
    *returnSize = 0;
    int **ret = NULL;
    if (intervalsSize == 0 || intervals == NULL) {
        return NULL;
    }

    qsort(intervals, intervalsSize, sizeof(int *), compare);

    int l = intervals[i][0];
    int r = intervals[i][1];

    while(i < intervalsSize) {
        l = intervals[i][0];
        r = intervals[i][1];
        while (i + 1  < intervalsSize ) {
            if (intervals[i+1][0] >= l && intervals[i+1][0] <= r) {
                if (intervals[i+1][1] > r) {
                    r = intervals[i+1][1];
                }
            } else {
                break;
            }
            i++;
        }

        add(&ret, *returnSize, l, r);
        (*returnSize)++;
        i++;
    }
    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    for (int r = 0; r < (*returnSize); r++)
    {
        (*returnColumnSizes)[r] = 2;    
    }
    return ret;
}

#define INTERVAL_ROWS 2
int g_intervals[][2] = 
{
    {1,4},
    {2, 3}
};

int main()
{
    int **intervals = (int **)malloc(sizeof(int *) * INTERVAL_ROWS);
    for (int r = 0; r < INTERVAL_ROWS; r++) {
        intervals[r] = (int *)malloc(sizeof(int) * 2);
        intervals[r][0] = g_intervals[r][0];
        intervals[r][1] = g_intervals[r][1];
    }

    int colSize = 2;
    int retSz = 0;
    int *retColSz;
    int **out = merge(intervals,INTERVAL_ROWS, &colSize, &retSz, &retColSz);
    for (int r = 0; r < retSz; r++) {
        printf("[%d %d]\n", out[r][0], out[r][1]);
        free(out[r]);
    }
    free(out);
    free(retColSz);
}