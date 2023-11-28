#include <stdlib.h>
#include <stdio.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

int minSubArrayLen(int target, int* nums, int numsSize) {
    int l = 0;
    int r = 1;

    int sum = nums[l];
    int ret = 0;

    // window should be [l, r)
    while(l < r) {
        // r -> maximum
        while(sum < target && r < numsSize) {
            sum += nums[r];
            r++;
        }
        if (sum < target) {
            break;
        }

        // shrink l
        while(l < r && sum - nums[l] >= target) {
            sum -= nums[l];
            l++;
        }

        // caculate min len
        ret = (ret == 0) ? (r-l) : min(ret, r-l);

        // next l
        if (l == (numsSize - 1)) {
            break;
        }
        sum -= nums[l];
        l++;
    }
    return ret;
}

int nums[] = {10,5,13,4,8,4,5,11,14,9,16,10,20,8};
int target = 80;

int main()
{
    printf("min len: %d.\n", minSubArrayLen(target, nums, sizeof(nums)/sizeof(int)));
}