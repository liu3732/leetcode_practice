#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <uthash.h>

typedef struct {
    int key;
    int val;
    UT_hash_handle hh;
} map_t;

bool add_map(map_t **map, int key, int val)
{
    bool ret = true;

    map_t *cur;
    HASH_FIND_INT(*map, &key, cur);
    if (cur == NULL) {
        cur = (map_t *)malloc(sizeof(map_t));
        cur->key = key;
        cur->val = val;
        HASH_ADD_INT(*map, key, cur);
        ret = true;
    } else if (cur->val != val) {
        ret = false;
    }
    return ret;
}

void free_map(map_t *map)
{
    map_t *cur, *tmp;
    HASH_ITER(hh, map, cur, tmp) {
        HASH_DEL(map, cur);
        free(cur);
    }
}

bool isIsomorphic(char* s, char* t) {
    int len = strlen(s);
    map_t *map = NULL, *tmap = NULL;
    bool ret = true;

    if (len != strlen(t)) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        int s_k = (int )s[i];
        int t_k = (int )t[i];

        if ((ret = add_map(&map, s_k, t_k)) == false) {
            break;
        }

        if ((ret = add_map(&tmap, t_k, s_k)) == false) {
            break;
        } 
    }
    free_map(map);
    free_map(tmap);
    return ret;
}

char *s = "badc";
char *t = "baba";

int main()
{
    printf("%d.\n", isIsomorphic(s, t));    
}