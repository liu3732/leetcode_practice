#include <stdlib.h>
#include <uthash.h>
#include "graph.h"
#include <assert.h>

/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numNeighbors;
 *     struct Node** neighbors;
 * };
 */

struct Entry {
    int val;
    struct Node *source;
    struct Node *cloned;
    UT_hash_handle hh;    
};


void freeMap(struct Entry *h)
{
    struct Entry *el, *tmp;
    HASH_ITER(hh, h, el, tmp)
    {
        HASH_DEL(h, el);
        free(el);
    }
}

struct Entry *createEntry(struct Node *s)
{
    struct Entry *ret = (struct Entry *)malloc(sizeof(struct Entry));
    ret->val = s->val;
    ret->source = s;
    return ret;
}

void dfsCollectNodes(struct Node *s, struct Entry **htble)
{
    struct Entry *elem = createEntry(s);
    HASH_ADD_INT(*htble, val, elem);

    for (int i = 0; i < s->numNeighbors; i++) {
        HASH_FIND_INT(*htble, &s->neighbors[i]->val, elem);
        if (!elem) {
            dfsCollectNodes(s->neighbors[i], htble);
        }
    }
}

struct Node *cloneGraph(struct Node *s) {
    if (s == NULL) {
        return NULL;
    }
    
    struct Entry *hashTable = NULL;

    dfsCollectNodes(s, &hashTable);

    struct Entry *el, *tmp;
    HASH_ITER(hh, hashTable, el, tmp)
    {
        el->cloned = (struct Node *)malloc(sizeof(struct Node));
        el->cloned->val = el->val;
        el->cloned->numNeighbors = el->source->numNeighbors;
        el->cloned->neighbors = (struct Node **)malloc(sizeof(struct Node *) * el->cloned->numNeighbors);
    }

    HASH_ITER(hh, hashTable, el, tmp)
    {
        int numNeighbors = el->source->numNeighbors;
        for (int i = 0; i < numNeighbors; i++) {
            struct Entry *tmp;
            HASH_FIND_INT(hashTable, &el->source->neighbors[i]->val, tmp);
            assert(tmp != NULL);
            el->cloned->neighbors[i] = tmp->cloned;
        }
    }

    struct Entry *out;
    HASH_FIND_INT(hashTable, &s->val, out);
    struct Node *ret = out->cloned;

    freeMap(hashTable);
    return ret;
}


#define ROW 4
#define COL 2
int g_input[][COL] = {
    {2, 4},
    {1, 3},
    {2, 4},
    {1, 3}
};

int main()
{
    int **in = (int **)malloc(ROW * sizeof(int *));
    for (int r = 0; r < ROW; r++) {
        in[r] = g_input[r];
    }
    int *colLen = (int *)malloc(ROW *sizeof(int));
    for (int r = 0; r < ROW; r++) {
        colLen[r] = COL;
    }

    struct Node *source = createListGraph(in, ROW, colLen);

    struct Node *cloned = cloneGraph(source);

    freeListGraph(source);
    freeListGraph(cloned);

    free(in);
    free(colLen);
}