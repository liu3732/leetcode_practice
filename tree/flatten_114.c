#include "bin_tree.h"
#include <sys/queue.h>
#include <stdlib.h>
#include <stdio.h>

struct q_entry {
    struct TreeNode *node;
    TAILQ_ENTRY(q_entry) field;
};

static TAILQ_HEAD(q_head, q_entry) g_qhead = TAILQ_HEAD_INITIALIZER(g_qhead);

void PutTreeNodeToQ(struct TreeNode *node)
{
    if (node == NULL) {
        return;
    }
    struct q_entry *elem = malloc(sizeof(struct q_entry));
    elem->node = node;
    TAILQ_INSERT_HEAD(&g_qhead, elem, field);

    PutTreeNodeToQ(node->left);
    PutTreeNodeToQ(node->right);
    return;    
}

void FreeQ()
{
    struct q_entry *cur = NULL;
    while(!TAILQ_EMPTY(&g_qhead)) {
        cur = TAILQ_FIRST(&g_qhead);
        TAILQ_REMOVE(&g_qhead, cur, field);
        free(cur);
    }
    return;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
void flatten(struct TreeNode* root) {
    if(root == NULL) {
        return;
    }
    
    PutTreeNodeToQ(root);

    struct q_entry *prev = NULL;
    struct q_entry *cur = NULL;

    TAILQ_FOREACH_REVERSE(cur, &g_qhead, q_head, field)
    {
        if(prev == NULL) {
            prev = cur;
        } else {
            prev->node->left = NULL;
            prev->node->right = cur->node;
            prev = cur;
        }
    }
    prev->node->left = NULL;
    prev->node->right = NULL;

    FreeQ();
}

int a[] = {1, 2, 5, 3, 4, NULL_NODE, 6};

int main(void)
{
    struct TreeNode *tree = LayerArrayToTree(a, sizeof(a)/sizeof(int));

    flatten(tree);
    printf("the test has been successed.\n");
    return 0;
}