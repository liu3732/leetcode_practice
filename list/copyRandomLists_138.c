#include <stdlib.h>
#include <uthash.h>
#include <stdio.h>

#define NULL_NODE INT32_MAX

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     struct Node *next;
 *     struct Node *random;
 * };
 */

struct Node {
    int val;
    struct Node *next;
    struct Node *random;
};

struct Node *dupNodeVal(struct Node *node) {
    struct Node *ret = (struct Node *)malloc(sizeof(struct Node));
    ret->val = node->val;
    ret->next = NULL;
    ret->random = NULL;
    return ret;
}

struct entry {
    struct Node *ptr;
    struct Node *match;

    UT_hash_handle hh;
};

typedef struct entry hash_t;

struct Node* copyRandomList(struct Node* head) {
    if (head == NULL) {
        return NULL;
    }
    
    hash_t *map = NULL;
    struct Node *k = head;

    while (k != NULL) {
        struct Node *v = dupNodeVal(k);
        hash_t *h_entry = (hash_t *)malloc(sizeof(hash_t));
        h_entry->ptr = k;
        h_entry->match = v;
        HASH_ADD_PTR(map, ptr, h_entry);

        k = k->next;
    }

    k = head;
    while(k != NULL) {
        hash_t *dup_one = NULL;
        HASH_FIND_PTR(map, &k, dup_one);
        struct Node *dup_node = dup_one->match;

        if (k->next) {
            HASH_FIND_PTR(map, &k->next, dup_one);
            dup_node->next = dup_one->match;
        }

        if (k->random) {
            HASH_FIND_PTR(map, &k->random, dup_one);
            dup_node->random = dup_one->match;
        }
        k = k->next;
    }

    hash_t *result;
    HASH_FIND_PTR(map, &head, result);
    struct Node *ret = result->match;

    hash_t *el;
    hash_t *tmp;
    HASH_ITER(hh, map, el, tmp)
    {
        HASH_DEL(map, el);
        free(el);
    }

    return ret;
}

struct Node *getXthNode(int xth, struct Node *dummy_head)
{
    if(xth == NULL_NODE) {
        return NULL;
    }

    struct Node *head = dummy_head;
    for (int i = 0; i < (xth+1); i++) {
        head = head->next;
    }
    return head;
}

struct Node *createRandomLists(int *radidxs, int *datas, int len)
{
    struct Node *h = (struct Node *)malloc(sizeof(struct Node));
    h->next = NULL;

    struct Node *cur = h;

    for (int i = 0; i < len; i++)
    {
        struct Node *nxt = NULL;
        nxt = (struct Node *)malloc(sizeof(struct Node));
        nxt->val = datas[i];
        nxt->next = NULL;
        cur->next = nxt;

        cur = nxt;
    }

    struct Node *ret = h->next;

    cur = ret;
    for (int i = 0; i < len; i++)
    {
        
        struct Node *random = getXthNode(radidxs[i], h);
        cur->random = random;
        cur = cur->next;
    }

    free(h);
    return ret;
}

void printRandomLists(struct Node *head)
{
    while (head != NULL) {
        printf("%d, %d; ", head->val, head->random ? head->random->val : -1111);
        
        struct Node *tmp = head->next;
        free(head);
        head = tmp;
    }
    printf("\n");
}

int g_d[] = {1,2};
int g_r[] = {1,1};

int main()
{
    struct Node *ret = createRandomLists(g_r, g_d, sizeof(g_d)/sizeof(int));
    printRandomLists(ret);

}