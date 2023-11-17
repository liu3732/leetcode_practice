#include <stdio.h>
#include <assert.h>

int removeElement(int* nums, int numsSize, int val) {
    if (numsSize == 0) {
        return 0;
    }

    if (numsSize == 1) {
        if(nums[0] == val) {
            return 0;
        } else {
            return 1;
        }
    }

    int leftLen = removeElement(&nums[1], numsSize-1, val);
    if (nums[0] == val) {
        for (int n = 0; n < leftLen; n++) {
            nums[n] = nums[n+1];
        }
        return leftLen;
    } else {
        return leftLen + 1;
    }
}

int a[] = {1};

int main()
{
    int expectedLen = 1;
    int v = 2;
    assert(expectedLen == removeElement(a, sizeof(a)/sizeof(int), v));
    for (int i = 0; i < expectedLen; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}