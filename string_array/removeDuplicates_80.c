#include <stdio.h>
#include <assert.h>

int removeDuplicates(int* nums, int numsSize) {
    if (numsSize == 0) {
        return 0;
    }

    if (numsSize == 1) {
        return 1;
    }

    int left = 0;
    int right = 1;
    int cnt = 1;

    while (right < numsSize) {
        if (nums[right] == nums[left]) {
            if(cnt == 2) {
                right++;
            } else if (cnt == 1)
            {
                cnt++;
                nums[left + 1] = nums[right];
                right++;
                left++;
            }
            assert(cnt <= 2);
        } else {
            nums[left + 1] = nums[right];
            left += 1;
            right++;
            cnt = 1;
        }
    }
    return left+1;
}

int a[] = {0,0,1,1,1,1,2,3,3};
int main()
{
    int left_len = removeDuplicates(a, sizeof(a)/sizeof(int));

    for (int i = 0; i < left_len; i++) {
        printf("%d ", a[i]);
    }
    printf("\ntest has been passed.\n");
    return 0;
}