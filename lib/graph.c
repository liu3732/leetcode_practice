#include "graph.h"
#include "uthash.h"
#include <stdlib.h>
#include <assert.h>

struct HashEntry {
    int v;
    struct Node *node;
    UT_hash_handle hh;
};

struct Node *createListGraph(int **input, int inputLen, int *colLens)
{
    struct HashEntry *set = NULL;

    // first init all nodes.
    for (int v = 1; v <= inputLen; v++) {
        struct HashEntry *out;
        HASH_FIND_INT(set, &v, out);
        if (!out) {
            struct Node *elem = (struct Node *)malloc(sizeof(struct Node));
            out = (struct HashEntry *)malloc(sizeof(struct HashEntry));
            out->v = v;
            out->node = elem;
            elem->val = v;
            elem->numNeighbors = colLens[v-1];
            elem->neighbors = (struct Node **)malloc(sizeof(struct Node *) * elem->numNeighbors);
            HASH_ADD_INT(set, v, out);
        } 
    }

    // second init all Node's Listed Node.
    for (int v = 1; v <= inputLen; v++) {
        struct HashEntry *out;
        HASH_FIND_INT(set, &v, out);
        assert(out != NULL);

        int listLen = colLens[v-1];
        int *listHead = input[v-1];
        struct Node *elem = out->node;
        for (int i = 0; i < listLen; i++) {
            struct HashEntry *listEntry;
            HASH_FIND_INT(set, &listHead[i], listEntry);
            assert(listEntry != NULL);
            elem->neighbors[i] = listEntry->node;
        }
    }

    struct Node *ret;
    int v = 1;
    struct HashEntry *out;
    HASH_FIND_INT(set, &v, out);
    assert(out != NULL);
    ret = out->node;

    // free set
    struct HashEntry *el, *tmp;
    HASH_ITER(hh, set, el, tmp)
    {
        HASH_DEL(set, el);
        free(el);
    }

    return ret;
}

void dfs_collect_nodes(struct HashEntry **hmap, struct Node *node)
{
    struct HashEntry *el;
    HASH_FIND_INT(*hmap, &node->val, el);
    assert(el == NULL);

    el = (struct HashEntry *)malloc(sizeof(struct HashEntry));
    el->node = node;
    el->v = node->val;
    HASH_ADD_INT(*hmap, v, el);

    for (int i = 0; i < node->numNeighbors; i++) {
        el = NULL;
        HASH_FIND_INT(*hmap, &node->neighbors[i]->val, el);
        if (!el) {
            dfs_collect_nodes(*hmap, node->neighbors[i]);
        }
    }
    return;
}

void freeListGraph(struct Node *node)
{
    struct HashEntry *nodes_to_be_deleted = NULL;
    dfs_collect_nodes(&nodes_to_be_deleted, node);

    struct HashEntry *el, *tmp;
    HASH_ITER(hh, nodes_to_be_deleted, el, tmp) {
        HASH_DEL(nodes_to_be_deleted, el);
        free(el->node->neighbors);
        free(el->node);
        free(el);
    }
    return;
}
