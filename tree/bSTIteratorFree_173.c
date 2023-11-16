#include "bin_tree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/queue.h>
#include <assert.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct elem_t {
    int v;
    TAILQ_ENTRY(elem_t) field;
};

TAILQ_HEAD(queue_t, elem_t);

typedef struct {
    struct queue_t q;
} BSTIterator;


void pushTreeInQ(struct TreeNode* root, struct queue_t *q)
{
    if(root == NULL) {
        return;
    }
    struct elem_t *new_elem = NULL;

    pushTreeInQ(root->left, q);
    new_elem = (struct elem_t *)malloc(sizeof(struct elem_t));
    new_elem->v = root->val;
    TAILQ_INSERT_HEAD(q, new_elem, field);
    pushTreeInQ(root->right, q);
}

BSTIterator* bSTIteratorCreate(struct TreeNode* root) {
    BSTIterator *ret = (BSTIterator *)malloc(sizeof(BSTIterator));
    TAILQ_INIT(&ret->q);

    pushTreeInQ(root, &ret->q);
    return ret;
}

int bSTIteratorNext(BSTIterator* obj) {
    assert(TAILQ_EMPTY(&obj->q) == false);
    struct elem_t *node = TAILQ_LAST(&obj->q, queue_t);
    int ret = node->v;
    
    TAILQ_REMOVE(&obj->q, node, field);
    free(node);
    return ret;
}

bool bSTIteratorHasNext(BSTIterator* obj) {
    return !TAILQ_EMPTY(&obj->q);
}

void bSTIteratorFree(BSTIterator* obj) {
    while(!TAILQ_EMPTY(&obj->q))
    {
        struct elem_t *node = TAILQ_LAST(&obj->q, queue_t);
        TAILQ_REMOVE(&obj->q, node, field);
        free(node);
    }
    free(obj);
}

/**
 * Your BSTIterator struct will be instantiated and called as such:
 * BSTIterator* obj = bSTIteratorCreate(root);
 * int param_1 = bSTIteratorNext(obj);
 
 * bool param_2 = bSTIteratorHasNext(obj);
 
 * bSTIteratorFree(obj);
*/

int a[] = {7, 3, 15, null, null, 9, 20};

int main()
{
    struct TreeNode* tree = LayerArrayToTree(a, sizeof(a)/sizeof(int));
    BSTIterator *bsIterator = bSTIteratorCreate(tree);
    assert(bSTIteratorNext(bsIterator) == 3);
    assert(bSTIteratorNext(bsIterator) == 7);
    assert(bSTIteratorHasNext(bsIterator) == true);
    assert(bSTIteratorNext(bsIterator) == 9);
    assert(bSTIteratorHasNext(bsIterator) == true);
    assert(bSTIteratorNext(bsIterator) == 15);
    assert(bSTIteratorHasNext(bsIterator) == true);
    assert(bSTIteratorNext(bsIterator) == 20);
    assert(bSTIteratorHasNext(bsIterator) == false);
    printf("the test has been passed\n");
}