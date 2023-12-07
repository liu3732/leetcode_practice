#include <stdbool.h>
#include <uthash.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
    int k;
    int id;
    UT_hash_handle hh;
} map_t;

map_t *get_in_map(map_t *m, int key)
{
    map_t *cur = NULL;
    HASH_FIND_INT(m, &key, cur);
    return cur;
}

int abs(int a) {
    if (a < 0) {
        return -a;
    } else {
        return a;
    }
}

void add_map(map_t **m, int key, int v)
{
    map_t *add = (map_t *)malloc(sizeof(map_t));
    add->k = key;
    add->id = v;
    HASH_ADD_INT(*m, k, add);
}

void free_map(map_t *m)
{
    map_t *cur, *tmp;
    HASH_ITER(hh, m, cur, tmp)
    {
        HASH_DEL(m, cur);
        free(cur);
    }
}

bool containsNearbyDuplicate(int* nums, int numsSize, int k) {
    map_t *m = NULL;
    bool ret = false;

    for (int i = 0; i < numsSize; i++)
    {
        map_t *cur;
        if((cur = get_in_map(m, nums[i])) != NULL) {
            int distance = abs(cur->id-i);
            assert(distance != 0);
            if (distance <= k) {
                ret = true;
                break;
            } else {
                HASH_DEL(m, cur);
                add_map(&m, nums[i], i);
            }
        } else {
            add_map(&m, nums[i], i);
        }
    }
    free_map(m);
    return ret;
}

int g_nums[] = {1,0,1,1};

int main()
{
    int k = 1;
    printf("%d\n",containsNearbyDuplicate(g_nums, sizeof(g_nums)/sizeof(int), k));
}