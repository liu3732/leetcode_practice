#include <stdlib.h>
#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* productExceptSelf(int* nums, int numsSize, int* returnSize) {
    
    *returnSize = numsSize;
    int *retArray = NULL;
    if(numsSize == 0) {
        return retArray;
    }

    retArray = (int *)malloc(numsSize * sizeof(int));
    int *leftA = (int *)malloc(numsSize * sizeof(int));
    int *rightA = (int *)malloc(numsSize * sizeof(int));

    // iterate
    leftA[0] = 1;
    for (int i = 1; i < numsSize; i++) {
        leftA[i] = leftA[i-1]*nums[i-1];
    }

    rightA[numsSize-1] = 1;
    for (int i = numsSize-2; i >= 0; i--) {
        rightA[i] = rightA[i+1]*nums[i+1];
    }

    for (int i = 0; i < numsSize; i++) {
        retArray[i] = leftA[i]*rightA[i];
    }
    free(leftA);
    free(rightA);
    return retArray;
}

int a[] = {2};

int main()
{
    int retsize = 0;
    int *b = productExceptSelf(a, sizeof(a)/sizeof(int), &retsize);
    for (int i = 0; i < retsize; i++) {
        printf("%d ", b[i]);
    }
    printf("\n");
}