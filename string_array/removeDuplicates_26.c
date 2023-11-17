#include <assert.h>
#include <stdio.h>

int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }
    if (numsSize == 1) {
        return 1;
    }

    int left = 0;
    int right = 1;
    while (right < numsSize) {
        if(nums[left] == nums[right]) {
            right++;
        } else {
            nums[left+1] = nums[right];
            left++;
            right++;
        }
    }
    return left+1;
}

int a[] = {0,0,1,1,1,2,2,3,3,4};

int main()
{
    int left_len = removeDuplicates(a, sizeof(a)/sizeof(int));

    for (int i = 0; i < left_len; i++) {
        printf("%d ", a[i]);
    }
    printf("\ntest has been passed.\n");
    return 0;
}