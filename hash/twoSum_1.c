#include <stdlib.h>
#include <uthash.h>
#include <stdio.h>

typedef struct {
    int key;
    int idx;
    UT_hash_handle hh;
} map_t;

void add(map_t **m, int k, int v)
{
    map_t *cur;
    HASH_FIND_INT(*m, &k, cur);
    if (cur != NULL) {
        return;
    }

    cur = (map_t *)malloc(sizeof(map_t));
    cur->key = k;
    cur->idx = v;
    HASH_ADD_INT(*m, key, cur);
    return;
}

void free_map(map_t *m)
{
    map_t *el, *tmp;
    HASH_ITER(hh, m, el, tmp)
    {
        HASH_DEL(m, el);
        free(el);
    }
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* twoSum(int* nums, int numsSize, int target, int* returnSize) {
    int *ret = NULL;
    *returnSize = 0;

    if (numsSize == 0) {
        return ret;
    }

    map_t *m = NULL;

    for (int i = 0; i < numsSize; i++) {
        add(&m, nums[i], i);
        map_t *another;

        int key = target - nums[i];
        HASH_FIND_INT(m, &key, another);
        if (another != NULL && another->idx != i) {
            ret = (int *)malloc(sizeof(int) * 2);
            ret[0] = i;
            ret[1] = another->idx;
            *returnSize = 2;
            break;        
        }
    }

    free_map(m);
    return ret;
}

#define LEN 4
int g_nums[LEN] = {2, 7, 11, 15};

int main()
{
    int target = 9;
    int ret_size = 0;

    int *ret = twoSum(g_nums, LEN, target, &ret_size);
    for (int i = 0; i < ret_size; i++) {
        printf("%d ", ret[i]);
    }
    printf("\n");
    free(ret);
}