#include "bin_tree.h"
#include <sys/queue.h>
#include <stdlib.h>

struct elem_t {
    struct TreeNode* node;
    TAILQ_ENTRY(elem_t) field;
};

TAILQ_HEAD(queue_t, elem_t);

void EnQueElem(struct TreeNode *node, struct queue_t *queue)
{
    struct elem_t *elem = (struct elem_t *)malloc(sizeof(struct elem_t));
    elem->node = node;
    TAILQ_INSERT_HEAD(queue, elem, field);
    return;
}

void putNodesAncestor(struct TreeNode *root, struct TreeNode *target, struct queue_t *queue)
{
    if (root == target) {

    }
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* lowestCommonAncestor(struct TreeNode* root, struct TreeNode* p, struct TreeNode* q) {
    struct queue_t queue_p, queue_q;
    TAILQ_INIT(&queue_p);
    TAILQ_INIT(&queue_q);

    putNodesAncestor(root, p, &queue_p);
    int len_p = getQlen(queue_p);
    
    putNodesAncestor(root, q, &queue_q);
    int len_q = getQlen(queue_q);

    if (len_p > len_q) {
        common = search_elems(&queue_q, &queue_p);
    } else {
        common = search_elems(&queue_p, &queue_q);
    }
    return common;
}

int main()
{
    return 0;
}