#include <stdbool.h>
#include <string.h>
#include <uthash.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    char *word; /* key*/
    int ch;
    UT_hash_handle hh;
} word_map_t;

typedef struct {
    int ch; /*key*/
    char *word; /* val */
    UT_hash_handle hh;
} ch_map_t;

char **split_blank(const char *input, int *out_len)
{
    char **ret = NULL;
    *out_len = 0;
    
    const char *prev = input;
    const char *next = strchr(prev, ' ');
    
    while (prev != NULL && *prev != '\0') {
        if (next == NULL) {
            int len = strlen(prev);
            ret = (char **)realloc(ret, ((*out_len) + 1)*sizeof(char *));
            ret[*out_len] = (char *)malloc(sizeof(char) * (len + 1));
            strncpy(ret[*out_len], prev, len);
            ret[*out_len][len] = '\0';
            (*out_len)++;
            break;
        } else {
            int len = next - prev;
            ret = (char **)realloc(ret, ((*out_len) + 1)*sizeof(char *));
            ret[*out_len] = (char *)malloc(sizeof(char) * (len + 1));
            strncpy(ret[*out_len], prev, len);
            ret[*out_len][len] = '\0';
            (*out_len)++;
        }
        prev = next + 1;
        next = strchr(prev, ' ');
    }
    return ret;
}

bool add_word_map(word_map_t **wmap, char *word, int ch)
{
    bool ret = true;

    word_map_t *cur;

    HASH_FIND_STR(*wmap, word, cur);
    if (cur == NULL) {
        cur = (word_map_t *)malloc(sizeof(word_map_t));
        cur->word = word;
        cur->ch = ch;
        HASH_ADD_STR(*wmap, word, cur);
    } else if (cur->ch != ch)
    {
        ret = false;
    }

    return ret;
}

bool add_ch_map(ch_map_t **cmap, int ch, char *word)
{
    bool ret = true;
    ch_map_t *cur;
    
    HASH_FIND_INT(*cmap, &ch, cur);
    if (cur == NULL) {
        cur = (ch_map_t *)malloc(sizeof(ch_map_t));
        cur->ch = ch;
        cur->word = word;
        HASH_ADD_INT(*cmap, ch, cur);
        ret = true;
    } else 
    {
        int len_a = strlen(cur->word);
        int len_b = strlen(word);
        if (len_a != len_b) {
            ret = false;
        } else if (strncmp(cur->word, word, strlen(word)) != 0)
        {
            ret = false;
        } else {
            ret = true;
        }
    }
    return ret;    
}

void free_ch_map(ch_map_t *m)
{
    ch_map_t *el, *tmp;
    HASH_ITER(hh, m, el, tmp)
    {
        HASH_DEL(m, el);
        free(el);
    }
}

void free_word_map(word_map_t *m)
{
    word_map_t *el, *tmp;
    HASH_ITER(hh, m, el, tmp)
    {
        HASH_DEL(m, el);
        free(el);
    }
}

bool wordPattern(char* pattern, char* s) {
    int len_p = strlen(pattern);

    int len_s = 0;
    char **words = split_blank(s, &len_s);

    if (len_p != len_s) {
        return false;
    }

    word_map_t *map_word = NULL;
    ch_map_t *map_ch = NULL;

    bool ret = true;
    for (int i = 0; i < len_p; i++) {
        int ch = (int )pattern[i];

        if((ret = add_word_map(&map_word, words[i], ch)) == false) {
            break;
        }
        if((ret = add_ch_map(&map_ch, ch, words[i])) == false) {
            break;
        }
    }

    free_ch_map(map_ch);
    free_word_map(map_word);

    for (int i = 0; i < len_p; i++) {
        free(words[i]);
    }
    free(words);

    return ret;
}

char *p = "abba";
char *s = "dog constructor constructo dog";

int main()
{
    printf("%d\n", wordPattern(p, s));
}