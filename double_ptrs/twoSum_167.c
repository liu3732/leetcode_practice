#include <stdlib.h>
#include <stdio.h>

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* numbers, int numbersSize, int target, int* returnSize) {
    int *ret = NULL;
    *returnSize = 0;

    int mid = target/2;
    if (target%2 && target < 0) {
        mid = target/2 - 1;
    }

    int l = -1;
    int r = -1;

    for (int i = 0; i < numbersSize; i++) {
        if(numbers[i] > mid) {
            r = i;
            break;
        } else if (numbers[i] <= mid)
        {
            l = i; // update every iterate to maximum
        }
    }
    if(l > 0 && l < numbersSize && numbers[l] == mid && numbers[l] + numbers[l-1] == target) {
        *returnSize = 2;
        ret = (int *)malloc(sizeof(int) * 2);
        ret[0] = l-1+1;
        ret[1] = l+1;
        return ret;
    }

    while (1) {
        if (l < 0 || r > (numbersSize - 1)) {
            return ret;
        }
        int sum = numbers[l] + numbers[r];
        if (sum == target) {
            *returnSize = 2;
            ret = (int *)malloc(sizeof(int) * 2);
            ret[0] = l+1;
            ret[1] = r+1;
            return ret;
        } else if (sum > target)
        {
            l--;
        } else if (sum < target) {
            r++;
        }
    }
    return ret; // impossible here;
}

int numbers[] = {0,0,3,4};
int target = 0;

int main()
{
    int size = 0;
    int *ret = twoSum(numbers, sizeof(numbers)/sizeof(int), target, &size);
    if (ret != NULL) {
        printf("numbers[%d] + numbers[%d] == %d.\n", ret[0], ret[1], numbers[ret[0]-1] + numbers[ret[1]-1]);
        free(ret);
    } else {
        printf("no found.\n");
    }
    return 0;
}