#include <stdio.h>
#include <assert.h>
#include <uthash.h>

struct hash_t {
    int v;
    UT_hash_handle hh;
};

void delete_all(struct hash_t *q_head) {
    struct hash_t *cur, *tmp;

    HASH_ITER(hh, q_head, cur, tmp) {
    HASH_DEL(q_head, cur);  /* delete it (users advances to next) */
    free(cur);             /* free it */
    }
}

int majorityElement(int* nums, int numsSize) {
    struct hash_t *visited_map = NULL;

    for (int i = 0; i < numsSize; i++) {
        int cnt = 1;

        struct hash_t *existed = NULL;
        HASH_FIND_INT(visited_map, &nums[i], existed);
        if(existed) {
            continue;
        }

        // check if nums[i] is MajorityElement or not.
        // we don't need to compare [0 ~ nums[i-1]).
        for (int j = i + 1; j < numsSize; j++) {
            if (nums[i] == nums[j]) {
                cnt++;
            }
        }
        if (cnt > numsSize/2) {
            delete_all(visited_map);
            return nums[i];
        }

        struct hash_t *new_elem = (struct hash_t *)malloc(sizeof(struct hash_t));
        new_elem->v = nums[i];
        HASH_ADD_INT(visited_map, v, new_elem);
    }
    printf("impossible here.\n");            
    return -1;
}

int a[] = {2,2,1,1,1,2,2};

int main()
{
    assert(majorityElement(a, sizeof(a)/sizeof(int)) == 2);
    printf("test has been passed.\n");
}