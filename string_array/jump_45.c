#include <stdio.h>
#include <stdlib.h>

#define INVALID_VAL 0x1fffffff

int jump(int* nums, int numsSize) {
    int *dp = (int *)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        dp[i] = INVALID_VAL;
    }

    dp[numsSize-1] = 0;
    for (int i = numsSize - 2; i >= 0; i--) {
        if (i + nums[i] >= numsSize - 1) {
            dp[i] = 1;
            continue;
        }

        int minStep = INVALID_VAL;
        for (int j = 1; j <= nums[i]; j++) {
            if (dp[i+j] != INVALID_VAL) {
                minStep = dp[i+j] < minStep ? dp[i+j] : minStep;
            }
        }
        dp[i] = minStep == INVALID_VAL ? INVALID_VAL : (minStep + 1);
    }
    int ret = dp[0];
    free(dp);
    return ret;
}

int a[] = {2, 3, 0, 1, 4};
int main()
{
    printf("min step: %d.\n", jump(a, sizeof(a)/sizeof(int)));
}