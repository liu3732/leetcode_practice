#include <string.h>
#include <stdlib.h>
#include <uthash.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#define MAX_WORD_LEN 30

typedef struct {
    char key[MAX_WORD_LEN+1];
    int cnt;
    UT_hash_handle hh;
} words_map_t;
char g_s[MAX_WORD_LEN+1];

void put_word(words_map_t **m, char *s, int len) {
    strncpy(g_s, s, len);
    g_s[len] = '\0';

    words_map_t *elem;
    HASH_FIND_STR(*m, g_s, elem);
    if (elem == NULL) {
        elem = (words_map_t *)malloc(sizeof(words_map_t));
        elem->cnt = 1;
        memcpy(elem->key, g_s, len+1);
        HASH_ADD_STR(*m, key, elem);
    } else {
        elem->cnt++;
    }
}

void delete_word(words_map_t **m, char *s, int len) {
    strncpy(g_s, s, len);
    g_s[len] = '\0';

    words_map_t *elem;
    HASH_FIND_STR(*m, g_s, elem);
    assert(elem != NULL);

    elem->cnt--;
    if (elem->cnt == 0) {
        HASH_DEL(*m, elem);
    }
}

bool compare_map(words_map_t *a, words_map_t *b) {
    if (HASH_COUNT(a) != HASH_COUNT(b)) {
        return false;
    }

    words_map_t *cur, *tmp;
    HASH_ITER(hh, a, cur, tmp) {
        words_map_t *cur_b = NULL;
        HASH_FIND_STR(b, cur->key, cur_b);
        if(cur_b == NULL || cur_b->cnt != cur->cnt) {
            return false;
        }
    }
    return true;
}

void free_map(words_map_t **m)
{
    words_map_t *cur, *tmp;
    HASH_ITER(hh, *m, cur, tmp)
    {
        free(cur);
    }
    *m = NULL;
}

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* findSubstring(char* s, char** words, int wordsSize, int* returnSize) {
    *returnSize = 0;
    if (wordsSize == 0 || words == NULL || s == NULL) {
        return NULL;
    }
    int len = strlen(s);
    int wordSize = strlen(words[0]);
    int windowSize = wordSize * wordsSize;
    int *ret = NULL;

    if (len < windowSize) {
        return NULL;
    }
    
    words_map_t *origin = NULL;
    words_map_t *win = NULL;

    // put words into map
    for (int i = 0; i < wordsSize; i++) {
        put_word(&origin, words[i], wordSize);
    }


    for (int j = 0; j < wordSize; j++) {
        free_map(&win);    
        for (int k = 0; k < wordsSize; k++) {
            put_word(&win, &s[j + k*wordSize], wordSize);
        }
        for (int i = 0; i <= len - windowSize; i += wordSize) {
            if(compare_map(origin, win) == true) {
                // add 
                ret = (int *)realloc(ret, ((*returnSize) + 1) * sizeof(int));
                ret[*returnSize] = j + i;
                (*returnSize)++;
            }
            if ((j + i + windowSize + wordSize - 1)>= len) {
                // window can't move on.
                break;
            }
            delete_word(&win, &s[j + i], wordSize);
            put_word(&win, &s[j + i + windowSize], wordSize);
        }
    }
    free_map(&win);
    free_map(&origin);
    return ret;
}

#define WORDS_SIZE 3
char *g_words[WORDS_SIZE] = {
    "bar",
    "foo",
    "the"
};

int main()
{
    char *s = "barfoofoobarthefoobarman";
    int wordSize = strlen(g_words[0]);

    char **words = (char **)malloc(WORDS_SIZE * sizeof(char *));
    for (int i = 0; i < WORDS_SIZE; i++) {
        words[i] = (char *)malloc((wordSize + 1)*sizeof(char));
        strncpy(words[i], g_words[i], wordSize+1);
    }

    int *ret = NULL;
    int retSize = 0;
    ret = findSubstring(s, words, WORDS_SIZE, &retSize);
    for (int i = 0; i < retSize; i++) {
        printf("%d ", ret[i]);
    }
    printf("\n");
    free(ret);
    return 0;
}