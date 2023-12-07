#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define MAX_STR_LEN 220
char g_str[MAX_STR_LEN];

char *malloc_new_range(int left, int right)
{
    char *ret_string = NULL;
    memset((char *)g_str, 0, MAX_STR_LEN);
    if (left == right) {
        sprintf(g_str, "%d", left);
    } else {
        sprintf(g_str, "%d->%d", left, right);
    }
    size_t len = strlen(g_str);
    ret_string = (char *)malloc(len+1);
    strncpy(ret_string, g_str, len+1);
    return ret_string;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
char ** summaryRanges(int* nums, int numsSize, int* returnSize)
{
    int left = 0;
    int right = 0;
    int step = 0;
    char **retRanges = NULL;
    *returnSize = 0;

    while(right < numsSize)
    {
        assert(nums[right] >= nums[left]);
        if((long) nums[right] == (long) nums[left] + step + 1) {
            right++;
            step++;
        } else if((long) nums[right] == (long) nums[left] + step) {
            right++;
        } else {
            char *new_range = malloc_new_range(nums[left], nums[right-1]);
            if (*returnSize == 0) {
                retRanges = (char **)malloc(sizeof(char **));
            } else {
                retRanges = (char **)realloc(retRanges, (*returnSize + 1) * sizeof(char **));
            }
            retRanges[*returnSize] = new_range;
            *returnSize += 1;
            left = right;
            right = left;
            step = 0;
        }
    }
    if (left < numsSize) {
        char *new_range = malloc_new_range(nums[left], nums[numsSize-1]);
        if (*returnSize == 0) {
            retRanges = (char **)malloc(sizeof(char **));
        } else {
            retRanges = (char **)realloc(retRanges, (*returnSize + 1) * sizeof(char **));
        }
        retRanges[*returnSize] = new_range;
        *returnSize += 1;
    }
    return retRanges;
}

int nums_01[] = {0, 2, 3, 4, 6, 8, 9};
int nums_00[] = {0, 1, 2, 4, 5, 7};
int nums_03[] = {0, 0, 0, 1,1,1,2,2};
int nums_04[] = {0};
int nums_05[] = {-2147483648,-2147483647,2147483647};

void free_string_array(char **p, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(p[i]);
    }
    free(p);
}

int main()
{
    int ret_size = 0;
    char **p = summaryRanges(nums_05, sizeof(nums_05)/sizeof(int), &ret_size);
    for (int i = 0; i < ret_size; i++)
    {
        printf("%s\n", p[i]);
    }

    free_string_array(p, ret_size);
}
