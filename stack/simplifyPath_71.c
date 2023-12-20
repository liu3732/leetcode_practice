#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/queue.h>
#include <stdbool.h>
#include <assert.h>

struct entry {
    char *word;
    TAILQ_ENTRY(entry) entries;
};

TAILQ_HEAD(queue_t, entry);

char *alloc_word_from(const char *path, int *wordLen)
{
    if (path == NULL || path[0] == '\0') {
        return NULL;
    }
    
    assert(path[0] == '/');
    
    *wordLen = 0;
    int i = 1;
    for (; i < strlen(path); i++) {
        if (path[i] == '/') {
            break;
        }
        (*wordLen)++;
    }
    
    if (*wordLen == 0) {
        return NULL;
    }
    char *ret = (char *)malloc((*wordLen) + 1);
    strncpy(ret, &path[1], *wordLen);
    ret[*wordLen] = '\0';
    return ret;
}

bool is_dot(const char *word)
{
    if (word == NULL) {
        return false;
    }
    if (strlen(word) == 1 && strncmp(word, ".", 1) == 0) {
        return true;
    }
    return false;
}

bool is_two_dot(const char *word)
{
    if (word == NULL) {
        return false;
    }

    if (strlen(word) == 2 && strncmp(word, "..", 2) == 0) {
        return true;
    }
    return false;
}


char *top(struct queue_t *qhead)
{
    struct entry *last_ele = TAILQ_LAST(qhead, queue_t);
    if (last_ele == NULL) {
        return NULL;
    }
    return last_ele->word;
}

char *pop(struct queue_t *qhead)
{
    struct entry *last_ele = TAILQ_LAST(qhead, queue_t);
    if (last_ele == NULL) {
        return NULL;
    }

    char *ret_word = last_ele->word;
    TAILQ_REMOVE(qhead, last_ele, entries);
    free(last_ele);
    return ret_word;
}

void push(struct queue_t *qhead, char *word)
{
    struct entry *new_entry = (struct entry *)malloc(sizeof(struct entry));
    new_entry->word = word;
    TAILQ_INSERT_TAIL(qhead, new_entry, entries);
}

int caculate_word_len(struct queue_t *qhead)
{
    struct entry *elem = NULL;
    int len = 0;
    TAILQ_FOREACH(elem, qhead, entries)
    {
        len += (1 + strlen(elem->word));
    }
    return len;
}

void free_queue(struct queue_t *qhead)
{
    struct entry *elem = NULL;

    while(!TAILQ_EMPTY(qhead))
    {
        elem = TAILQ_FIRST(qhead);
        TAILQ_REMOVE(qhead, elem, entries);
        free(elem->word);
        free(elem);
    }
}

char* simplifyPath(char* path) {
    if (path == NULL || path[0] != '/') {
        return NULL;
    }

    char *ret = NULL;
    int wlen = 0;
    struct queue_t queue;
    TAILQ_INIT(&queue);


    char *this_word = alloc_word_from(path, &wlen);
    while (path[0] != '\0')
    {
        if(wlen == 0 || is_dot(this_word)) {
            if (this_word) {
                free(this_word);
            }
        } else if (is_two_dot(this_word)) {
            free(this_word);
        
            char *last_word = pop(&queue);
            if(last_word) {
                free(last_word);
            }
        } else {
            push(&queue, this_word);
        }
        
        // update
        path = path + wlen + 1;
        this_word = alloc_word_from(path, &wlen);
    }

    int total_len = caculate_word_len(&queue);
    if (total_len == 0) {
        ret = (char *)malloc(2);
        ret[0] = '/';
        ret[1] = '\0';
    } else {
        ret = (char *)malloc(total_len + 1);

        struct entry *elem = NULL;
        int i = 0;
        TAILQ_FOREACH(elem, &queue, entries)
        {
            ret[i] = '/';
            int wlen = strlen(elem->word);
            strncpy(&ret[i+1], elem->word, wlen);
            i += (wlen + 1);
        }
        ret[i] = '\0';
    }
    free_queue(&queue);
    return ret;
}

int main()
{
    char *path = "/a/./b/../../c/";

    char *ret = simplifyPath(path);
    printf("%s\n", ret);
    free(ret);
}