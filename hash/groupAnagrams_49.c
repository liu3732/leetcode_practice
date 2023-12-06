#include <uthash.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>

#define MAX_CH_NUM 26

typedef struct {
    int ch_cnts[MAX_CH_NUM]; // key

    char **strs; 
    int str_cnt;
    UT_hash_handle hh;
} map_t;


void add_str_in_map(map_t *cur, char *str, int len)
{
    cur->strs = (char **) realloc(cur->strs, cur->str_cnt + 1);
    cur->strs[cur->str_cnt] = (char *)malloc(len + 1);
    strncpy(cur->strs[cur->str_cnt], str, len);
    cur->strs[cur->str_cnt][len] = '\0';
    cur->str_cnt++;
}

void str_to_key(int *key, int keyLen, char *str)
{
    int len = strlen(str);
    memset(key, 0, keyLen * sizeof(int));
    for (int i = 0; i < len; i++)
    {
        int idx = (int)(str[i] - 'a');
        key[idx]++;
    }
}

map_t *get_anagram_in_map(map_t *m, int *key)
{
    map_t *tmp;
    HASH_FIND(hh, m, key, MAX_CH_NUM*sizeof(int), tmp);
    return tmp;
}

void add_str_to_anagram(map_t *anagram, char *str)
{
    anagram->strs = (char **)realloc(anagram->strs, (anagram->str_cnt + 1)*sizeof(char *));
    anagram->strs[anagram->str_cnt] = str;
    anagram->str_cnt++;
}

void add_anagram_to_map(map_t **m, int *key, char *str)
{
    map_t *anagram = (map_t *)malloc(sizeof(map_t));
    anagram->str_cnt = 1;
    anagram->strs = (char **)malloc(anagram->str_cnt * sizeof(char *));
    anagram->strs[0] = str;
    memcpy(anagram->ch_cnts, key, MAX_CH_NUM*sizeof(int));
    HASH_ADD(hh, *m, ch_cnts, MAX_CH_NUM*sizeof(int), anagram);
}
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
char*** groupAnagrams(char** strs, int strsSize, int* returnSize, int** returnColumnSizes) {
    static int tmp_key[MAX_CH_NUM];

    map_t *m = NULL;
    map_t *cur;
    for (int i = 0; i < strsSize; i++) {
        str_to_key(tmp_key, MAX_CH_NUM, strs[i]);
        if ((cur = get_anagram_in_map(m, tmp_key)) != NULL) {
            add_str_to_anagram(cur, strs[i]);
        } else {
            add_anagram_to_map(&m, tmp_key, strs[i]);
        }
    }

    int groupLen = HASH_COUNT(m);
    char ***ret = (char ***)malloc(sizeof(char **) * groupLen);
    *returnColumnSizes = (int *)malloc(sizeof(int) * groupLen);
    *returnSize = groupLen;
    
    map_t *tmp;
    int i = 0;
    HASH_ITER(hh, m, cur, tmp)
    {
        (*returnColumnSizes)[i] = cur->str_cnt;
        ret[i] = cur->strs;
        i++;
        HASH_DEL(m, cur);
        free(cur);
    }
    return ret;
}

#define ROW 6
char *t_strs[] = {
    "hhhhu","tttti","tttit","hhhuh","hhuhh","tittt"
};

int main()
{
    char **test = (char **)malloc(ROW*sizeof(char*));
    for (int m = 0; m < ROW; m++) {
        test[m] = (char *)malloc(strlen(t_strs[m])+ 1);
        strncpy(test[m], t_strs[m], strlen(t_strs[m])+1);
    }

    int retSize = 0;
    int *retColumSize = NULL;
    char ***retS = groupAnagrams(test, ROW, &retSize, &retColumSize);
    for (int i = 0; i < retSize; i++) {
        for(int j = 0; j < retColumSize[i]; j++) {
            printf("%s ", retS[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < retSize; i++) {
        for(int j = 0; j < retColumSize[i]; j++) {
            free(retS[i][j]);
        }
        free(retS[i]);
    }
    free(retS);
    free(retColumSize);
}