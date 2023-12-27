#include <uthash.h>
#include <sys/queue.h>
#include <stdio.h>

struct DListNode {
    int key;
    int val;
    struct DListNode *prev;
    struct DListNode *next;
};

struct HashEntry {
    int key;
    struct DListNode *p;
    UT_hash_handle hh;
};

typedef struct {
    struct HashEntry *map;
    struct DListNode *head;
    struct DListNode *tail;
    int len;
    int capacity;
} LRUCache;


LRUCache* lRUCacheCreate(int capacity) {
    LRUCache *ret = (LRUCache *)malloc(sizeof(LRUCache));
    ret->map = NULL;
    ret->head = NULL;
    ret->tail = NULL;
    ret->len = 0;
    ret->capacity = capacity;
    return ret;
}

void moveNodeToHead(struct DListNode *n, struct DListNode **head, struct DListNode **tail)
{
    if (*head == *tail) {
        return;
    }

    if (n == *head) {
        return;
    }
    if (n == *tail) {
        *tail = n->prev;
        (*tail)->next = NULL;
        n->prev = NULL;
        n->next = *head;
        (*head)->prev = n;
        *head = n;
        return;
    }

    // n != head && n != tail
    struct DListNode *prev = n->prev;
    struct DListNode *nxt = n->next;
    prev->next = nxt;
    nxt->prev = prev;

    n->next = *head;
    n->prev = NULL;
    (*head)->prev = n;
    *head = n;
    return;
}

int lRUCacheGet(LRUCache* obj, int key) {
    struct HashEntry *out;
    HASH_FIND_INT(obj->map, &key, out);
    if (out) {
        moveNodeToHead(out->p, &obj->head, &obj->tail);
        return out->p->val;
    } else {
        return -1;
    }
}

void lRUCachePut(LRUCache* obj, int key, int value) {
    struct HashEntry *out;
    HASH_FIND_INT(obj->map, &key, out);
    if (out) {
        out->p->val = value;
        moveNodeToHead(out->p, &obj->head, &obj->tail);
    } else {
        out = (struct HashEntry *)malloc(sizeof(struct HashEntry));
        out->key = key;
        out->p = (struct DListNode *)malloc(sizeof(struct DListNode));
        out->p->key = key;
        out->p->val = value;
        out->p->next = obj->head;
        if(obj->head) {
            obj->head->prev = out->p;
        }
        out->p->prev = NULL;
        obj->head = out->p;
        if(!obj->tail) {
            obj->tail = obj->head;
        }

        HASH_ADD_INT(obj->map, key, out);
        if (obj->len < obj->capacity) {
            obj->len++;
        } else {
            struct DListNode *new_tail = obj->tail->prev;
            struct HashEntry *tail_entry;
            HASH_FIND_INT(obj->map, &obj->tail->key, tail_entry);
            HASH_DEL(obj->map, tail_entry);
            free(tail_entry);
            free(obj->tail);
            new_tail->next = NULL;
            obj->tail = new_tail;
        }
    }
}

void lRUCacheFree(LRUCache* obj) {
    struct HashEntry *el, *tmp;
    HASH_ITER(hh, obj->map, el, tmp)
    {
        HASH_DEL(obj->map, el);
        free(el->p);
        free(el);
    }
    free(obj);
}

/**
 * Your LRUCache struct will be instantiated and called as such:
 * LRUCache* obj = lRUCacheCreate(capacity);
 * int param_1 = lRUCacheGet(obj, key);
 
 * lRUCachePut(obj, key, value);
 
 * lRUCacheFree(obj);
*/

int main()
{
    LRUCache* obj = lRUCacheCreate(3);
    lRUCachePut(obj, 1, 1);
    lRUCachePut(obj, 2, 2);
    lRUCachePut(obj, 3, 3);
    lRUCachePut(obj, 4, 4);

    int v = lRUCacheGet(obj, 4);
    printf("%d\n", v);
    v = lRUCacheGet(obj, 3);
    printf("%d\n", v);
    v = lRUCacheGet(obj, 2);
    printf("%d\n", v);
    v = lRUCacheGet(obj, 1);
    printf("%d\n", v);

    lRUCachePut(obj, 5, 5);
    v = lRUCacheGet(obj, 1);
    printf("%d\n", v);
    v = lRUCacheGet(obj, 2);
    printf("%d\n", v);
    v = lRUCacheGet(obj, 3);
    printf("%d\n", v);
    v = lRUCacheGet(obj, 4);
    printf("%d\n", v);    
    v = lRUCacheGet(obj, 5);
    printf("%d\n", v);        
}