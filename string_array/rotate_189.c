#include <stdio.h>
#include <assert.h>

void reverse(int *nums, int len)
{
    for (int i = len - 1; i >= len/2; i--) {
        int tmp = nums[i];
        nums[i] = nums[len-1 - i];
        nums[len-1 - i] = tmp;
    }
    return;
}

void rotate(int* nums, int numsSize, int k) {
    if (numsSize == 1 || k == 0) {
        return;
    }
    int shift = k;
    if (k > numsSize) {
        shift = k%numsSize;
    }

    reverse(nums, numsSize-shift);
    reverse(&nums[numsSize-shift], shift);
    reverse(nums, numsSize);
}

int a[] = {-1, -100, 3, 99};
int k = 2;
int main()
{
    int len = sizeof(a)/sizeof(int);
    rotate(a, len, k);
    for (int i = 0; i < len; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}