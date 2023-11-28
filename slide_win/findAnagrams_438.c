#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <uthash.h>
#include <stdbool.h>
#include <assert.h>

typedef struct hash_entry {
    int key;
    int cnt;
    UT_hash_handle hh;
} map_t;


void put_map(map_t **m, char a)
{
    int k = (int )a;
    map_t *entry = NULL;
    HASH_FIND_INT(*m, &k, entry);
    if (entry == NULL) {
        entry = (map_t *)malloc(sizeof(map_t));
        entry->key = k;
        entry->cnt = 1;
        HASH_ADD_INT(*m, key, entry);
    } else {
        entry->cnt++;
    }
}

void delete_map(map_t **m, char a)
{
    int k = (int) a;
    map_t *entry = NULL;
    HASH_FIND_INT(*m, &k, entry);
    assert(entry != NULL);
    entry->cnt--;

    if (entry->cnt == 0) {
        HASH_DELETE(hh, *m, entry);
    }
}

bool compare_map(map_t *a, map_t *b)
{
    int len_a = HASH_COUNT(a);
    int len_b = HASH_COUNT(b);
    if (len_a != len_b) {
        return false;
    }

    map_t *elem_a, *tmp, *elem_b;
    HASH_ITER(hh, a, elem_a, tmp) {
        HASH_FIND_INT(b, &elem_a->key, elem_b);
        if (elem_b == NULL || elem_a->cnt != elem_b->cnt) {
            return false;
        }
    }
    return true;
}

void free_map(map_t *h)
{
    map_t *el, *tmp;
    HASH_ITER(hh, h, el, tmp) {
        free(el);
    }
    return;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findAnagrams(char * s, char * p, int* returnSize){
    int len = strlen(s);
    int w_len = strlen(p);
    int *ret = NULL;
    *returnSize = 0;

    if (len == 0 || w_len == 0 || len < w_len) {
        return ret;
    }

    // init
    map_t * h1 = NULL;
    for (int i = 0; i < w_len; i++) {
        put_map(&h1, p[i]);
    }

    map_t *window = NULL;
    for (int i = 0; i < w_len; i++) {
        put_map(&window, s[i]);
    }

    int i = 0;
    for (i = 0; i < (len - w_len + 1);) {
        if (compare_map(h1, window) == true) {
            // add
            ret = (int *)realloc(ret, (*returnSize + 1)* sizeof(int));
            ret[*returnSize] = i;
            (*returnSize)++;
        }

        delete_map(&window, s[i]);
        put_map(&window, s[i+w_len]);
        i++;
    }

    free_map(h1);
    free_map(window);
    return ret;
}

int main()
{
    char *s = "abab";
    char *p = "ab";
    int retSize = 0;

    int *ret = findAnagrams(s, p, &retSize);
    for (int r = 0; r < retSize; r++) {
        printf("%d ", ret[r]);
    }
    printf("\n");
}