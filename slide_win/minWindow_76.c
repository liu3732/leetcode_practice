#include <string.h>
#include <uthash.h> 
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    int key;
    int cnt;
    UT_hash_handle hh;
} map_t;

typedef struct {
    int min_len;
    int left;
    int right;
} ret_t;

void put_word(map_t **m, char k)
{
    int v = (int)k;
    map_t *cur = NULL;
    HASH_FIND_INT(*m, &v, cur);

    if (cur == NULL) {
        cur = (map_t *)malloc(sizeof(map_t));
        cur->cnt = 1;
        cur->key = v;
        HASH_ADD_INT(*m, key, cur);
    } else {
        cur->cnt++;
    }
}

void delete_word(map_t **m, char k)
{
    int v = (int)k;
    map_t *cur = NULL;
    HASH_FIND_INT(*m, &v, cur);
    assert(cur != NULL);
    if (cur->cnt == 1) {
        HASH_DEL(*m, cur);
    } else {
        cur->cnt--;
    }
    
}

bool is_cover(map_t *big, map_t *small)
{
    if (HASH_COUNT(big) < HASH_COUNT(small)) {
        return false;
    }

    map_t *cur, *tmp;
    HASH_ITER(hh, small, cur, tmp)
    {
        map_t *big_cur;
        HASH_FIND_INT(big, &cur->key, big_cur);
        if (big_cur == NULL || big_cur->cnt < cur->cnt) {
            return false;
        }
    }
    return true;
}

int get_cnt(map_t *m, char k)
{
    int v = k;
    map_t *cur;
    HASH_FIND_INT(m, &v, cur);
    if (cur == NULL) {
        return 0;
    } else {
        return cur->cnt;
    }
}

void free_map(map_t **m)
{
    map_t *el, *tmp;
    HASH_ITER(hh, *m, el, tmp) {
        free(el);
    }
    *m = NULL;
}

char* minWindow(char* s, char* t) {
    int len_s = strlen(s);
    int len_t = strlen(t);

    if (len_s < len_t) {
        return "";
    }

    map_t *base = NULL, *win = NULL;
    for (int i = 0; i < len_t; i++) {
        put_word(&base, t[i]);
    }

    for (int i = 0; i < len_t; i++) {
        put_word(&win, s[i]);
    }
    int l = 0, r = len_t; // [l, r) is window
    ret_t ret;
    ret.min_len = INT32_MAX;
    ret.left = -1;
    ret.right = -1;
    
    while(1) {
        while(r < len_s) {
            if (is_cover(win, base)) {
                break;
            }
            put_word(&win, s[r]);
            r++;
        }
        if (r == len_s && !is_cover(win, base)) {
            // no qualify r.
            break;
        }

        while(l < r) {
            if (get_cnt(win, s[l]) > get_cnt(base, s[l])) {
                delete_word(&win, s[l]);
                l++;
            } else {
                break;
            }
        }
        if (r-l < ret.min_len) {
            ret.min_len = r-l;
            ret.left = l;
            ret.right = r;
        }

        delete_word(&win, s[l]);
        l++;
    }
    free_map(&win);
    free_map(&base);

    if (ret.min_len == INT32_MAX) {
        return "";
    } else {
        char *min_str = (char *)malloc(ret.min_len + 1);
        strncpy(min_str, &s[ret.left], ret.min_len);
        min_str[ret.min_len] = '\0';
        return min_str;
    }
}

char *g_s = "a";
char *g_t = "aa";

int main()
{

    char *a = minWindow(g_s, g_t);
    printf("min win: %s.\n", a);
    free(a);
}