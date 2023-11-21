#include <stdbool.h>
#include <stdlib.h>
#include <uthash.h>
#include <assert.h>
#include <stdio.h>

#define MAX_LEN 200000
int g_a[MAX_LEN];

typedef struct {
    int *a;
    int len;
    struct hash_t *htable;
} RandomizedSet;

struct hash_t {
    int val;    /* key */
    int id;     /* array id */
    UT_hash_handle hh;
};

RandomizedSet* randomizedSetCreate() {
    RandomizedSet *ret = (RandomizedSet *)malloc(sizeof(RandomizedSet));
    ret->a = g_a;
    ret->len = 0;
    ret->htable = NULL;
    return ret;
}

bool randomizedSetInsert(RandomizedSet* obj, int val) {
    struct hash_t *elem = NULL;
    HASH_FIND_INT(obj->htable, &val, elem);
    if (elem != NULL) {
        return false;
    }
    obj->len++;
    obj->a[obj->len-1] = val;

    elem = (struct hash_t *)malloc(sizeof(struct hash_t));
    elem->val = val;
    elem->id = obj->len-1;
    HASH_ADD_INT(obj->htable, val, elem);
    return true;
}

bool randomizedSetRemove(RandomizedSet* obj, int val) {
    struct hash_t *elem = NULL;
    HASH_FIND_INT(obj->htable, &val, elem);
    if (elem == NULL) {
        return false;
    }
    struct hash_t *replaced = NULL;
    HASH_FIND_INT(obj->htable, &obj->a[obj->len-1], replaced);
    replaced->id = elem->id;
    
    obj->a[elem->id] = obj->a[obj->len-1];
    obj->len--;
    HASH_DEL(obj->htable, elem);
    free(elem);
    return true;
}

int randomizedSetGetRandom(RandomizedSet* obj) {
    int id = rand() % obj->len;
    return obj->a[id];    
}

void randomizedSetFree(RandomizedSet* obj) {
    obj->len = 0;
    struct hash_t *el, *tmp;
    HASH_ITER(hh, obj->htable, el, tmp)
    {
        HASH_DEL(obj->htable, el);
        free(el);
    }
    return;
}

/**
 * Your RandomizedSet struct will be instantiated and called as such:
 * RandomizedSet* obj = randomizedSetCreate();
 * bool param_1 = randomizedSetInsert(obj, val);
 
 * bool param_2 = randomizedSetRemove(obj, val);
 
 * int param_3 = randomizedSetGetRandom(obj);
 
 * randomizedSetFree(obj);
*/
int main()
{
    RandomizedSet *set = randomizedSetCreate();
    assert(true == randomizedSetInsert(set, 1));
    assert(false == randomizedSetRemove(set, 2));
    assert(true == randomizedSetInsert(set, 2));
    assert(2 == randomizedSetGetRandom(set) || 1 == randomizedSetGetRandom(set));
    assert(true == randomizedSetRemove(set, 1));
    assert(false == randomizedSetInsert(set, 2));
    assert(2 == randomizedSetGetRandom(set));
    randomizedSetFree(set);
    printf("test has been passed.\n");
    return 0;
}