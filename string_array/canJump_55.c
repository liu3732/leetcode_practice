#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

bool canJump_dfs(int* nums, int numsSize, int *dp, int cur) {
    assert(numsSize > 0);
    if (numsSize == 1) {
        dp[cur] = true;
        return true;
    }

    if (dp[cur] != -1) {
        return dp[cur];
    }

    int farestJump = nums[cur];
    if (farestJump >= numsSize-1-cur) {
        dp[cur] = true;
        return true;
    }

    if (farestJump == 0) {
        dp[cur] = false;
        return false;
    }

    for (int i = 1; i <= farestJump; i++) {
        if(canJump_dfs(nums, numsSize, dp, cur+i)) {
            dp[cur] = true;
            return true;
        }
    }
    dp[cur] = false;
    return dp[cur];
}

bool canJump(int* nums, int numsSize) {
    int *dp = (int *)malloc(numsSize*sizeof(int));
    for (int i = 0; i < numsSize; i++) {
        dp[i] = -1;
    }
    bool ret = canJump_dfs(nums, numsSize, dp, 0);
    free(dp);
    return ret;
}

int a[] = {2,3,1,1,4};
int main()
{
    assert(canJump(a, sizeof(a)/sizeof(int)) == true);
    printf("test has been passed.\n");
}