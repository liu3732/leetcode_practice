#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <uthash.h>

typedef struct {
    int id;
    int distance;
    UT_hash_handle hh;
} map_t;

void free_map(map_t *m)
{
    map_t *el, *tmp;
    HASH_ITER(hh, m, el, tmp)
    {
        HASH_DEL(m, el);
        free(el);
    }
}

void add_map(map_t **m, int id)
{
    map_t *out;
    HASH_FIND_INT(*m, &id, out);
    if(out == NULL) {
        out = (map_t *)malloc(sizeof(map_t));
        out->id = id;
        out->distance = 0;
        HASH_ADD_INT(*m, id, out);
    }
}

bool is_in_map(map_t *m, int id)
{
    map_t *out;
    HASH_FIND_INT(m, &id, out);
    if(out == NULL) {
        return false;
    } else {
        return true;
    }
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
     return a < b ? a : b;
}

int get_distance(map_t *m, int v)
{
    map_t *out = NULL;
    HASH_FIND_INT(m, &v, out);
    if (out == NULL) {
        return 0;
    } else if (out->distance > 0) {
        return out->distance;
    } else {
        return 1 + get_distance(m, v+1);
    }
}

void update_map(map_t *m, int v)
{
    map_t *out = NULL;
    HASH_FIND_INT(m, &v, out);
    if (out != NULL) {
        out->distance = get_distance(m, v);
    }
    return;
}

int longestConsecutive(int* nums, int numsSize) {
    if (numsSize == 0 || nums == NULL) {
        return 0;
    }
    map_t *m = NULL;

    for (int i = 0; i < numsSize; i++) {
        add_map(&m, nums[i]);
    }

    map_t *el, *tmp;
    HASH_ITER(hh, m, el, tmp)
    {
        if (el->distance > 0) {
            continue;
        }
        el->distance = get_distance(m, el->id);
    }

    int ret = 0;
    HASH_ITER(hh, m, el, tmp)
    {
        ret = max(ret, el->distance);
    }

    free_map(m);
    return ret;
}

int main()
{
    int nums[] = {0,3,7,2,5,8,4,6,0,1};

    printf("%d\n",longestConsecutive(nums, sizeof(nums)/sizeof(int)));
}