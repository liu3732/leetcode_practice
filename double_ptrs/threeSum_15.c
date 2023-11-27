#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
    int ia = *(int *)a;
    int ib = *(int *)b;

    return ia > ib;
}

int rightShiftNon(int i, int* nums, int rightBorder)
{
    int sft = 1;
    for(; (i + sft) <= rightBorder && nums[i] == nums[i+sft]; sft++) {

    }
    return i+sft;
}

int leftShiftNon(int i, int* nums, int leftBorder)
{
    int sft = 1;
    for(; (i - sft) >= leftBorder && nums[i] == nums[i-sft]; sft++) {

    }
    return i-sft;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** threeSum(int* nums, int numsSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = 0;
    int **retArray = NULL;
                
    // sort nums to increasing n*logn
    qsort(nums, numsSize, sizeof(int), compare);

    // iterate.
    for (int i = 0; i < numsSize-2;) {
        // nums[i] != nums[l + 1], but nums[i] may equal nums[l]
        int l = i+1;
        int r = numsSize - 1;


        int target = 0 - nums[i];
        while (l < r) {
            int current = nums[l] + nums[r];
            if (current < target) {
                l = rightShiftNon(l, nums, numsSize-1);
            } else if (current > target) {
                r = leftShiftNon(r, nums, 0);
            } else {
                (*returnSize)++;
                retArray = (int **)realloc(retArray, (*returnSize)*sizeof(int *));
                retArray[(*returnSize)-1] = (int *)malloc(sizeof(int) * 3);
            
                retArray[(*returnSize)-1][0] = nums[i];
                retArray[(*returnSize)-1][1] = nums[l];
                retArray[(*returnSize)-1][2] = nums[r];

                l = rightShiftNon(l, nums, numsSize-1);
                r = leftShiftNon(r, nums, 0);
            }
        }

        i = rightShiftNon(i, nums, numsSize-1);
    }

    *returnColumnSizes = (int *)malloc((*returnSize) * (sizeof(int)));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 3;
    }

    return retArray;
}

int main()
{
    int nums[] = {0,0,0};
    int *retColmunSize = NULL;
    int retSize = 0;

    int **ret = threeSum(nums, sizeof(nums)/sizeof(int), &retSize, &retColmunSize);
    free(retColmunSize);

    for (int i = 0; i < retSize; i++) {
        for (int c = 0; c < 3; c++) {
            printf("%d ", ret[i][c]);
        }
        free(ret[i]);
        printf("\n");
    }
    free(ret);
}