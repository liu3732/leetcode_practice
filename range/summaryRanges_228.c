#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** summaryRanges(int* nums, int numsSize, int* returnSize)
{
    int l = 0;
    int r = 1;
    static char buffer[30];
    char **ret = NULL;
    *returnSize = 0;

    while (l < numsSize) {
        r = l+1;
        while(r < numsSize && nums[r] == nums[l] + (r-l)) {
            r++;
        }

        // output nums[l] -> nums[r-1]
        if (l == r - 1) {
            sprintf(buffer, "%d", nums[l]);
        } else {
            sprintf(buffer, "%d->%d", nums[l], nums[r-1]);
        }        
        ret = (char **)realloc(ret, ((*returnSize) + 1)*sizeof(char *));
        ret[*returnSize] = (char *)malloc(strlen(buffer) + 1);
        strncpy(ret[*returnSize], buffer, strlen(buffer) + 1);
        (*returnSize)++;

        l = r;
    }
    return ret;
}

int main()
{
    int nums[] = {0,2,3,4,6,8,9};

    int returnSize = 0;
    char **ret = summaryRanges(nums, sizeof(nums)/sizeof(int), &returnSize);

    for (int i = 0; i < returnSize; i++) {
        printf("%s\n", ret[i]);
        free(ret[i]);
    }
    free(ret);
}