#include "bin_tree.h"
#include <stdlib.h>
#include <sys/queue.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

struct q_elem {
    int val;
    int multi;
    TAILQ_ENTRY(q_elem) field;
};

TAILQ_HEAD(q_head, q_elem) g_queue = TAILQ_HEAD_INITIALIZER(g_queue);


struct q_head *PutValuesToQ(struct TreeNode *root)
{
    if (root == NULL) {
        return NULL;
    }

    struct q_head *ret_q = NULL;

    struct q_head *l_q = PutValuesToQ(root->left);
    struct q_head *r_q = PutValuesToQ(root->right);
    
    if (l_q == NULL && r_q == NULL) {
        struct q_elem *elem = (struct q_elem *)malloc(sizeof(struct q_elem));
        elem->val = root->val;
        elem->multi = 1;

        ret_q = (struct q_head *)malloc(sizeof(struct q_head));
        TAILQ_INIT(ret_q);
        TAILQ_INSERT_HEAD(ret_q, elem, field);
        return ret_q;
    } else if (l_q == NULL && r_q != NULL) {
        ret_q = r_q;
    } else if (l_q != NULL && r_q == NULL) {
        ret_q = l_q;
    } else {
        TAILQ_CONCAT(l_q, r_q, field);
        free(r_q);
        ret_q = l_q;
    }

    struct q_elem *cur = NULL;
    TAILQ_FOREACH(cur, ret_q, field)
    {
        cur->val += cur->multi * 10 * root->val;
        cur->multi *= 10;
    }

    return ret_q;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int sumNumbers(struct TreeNode* root) {
    if (root == NULL) {
        return 0;
    }

    struct q_head *q = PutValuesToQ(root);
    
    int sum = 0;
    while(!TAILQ_EMPTY(q)) {
        struct q_elem *tmp = TAILQ_FIRST(q);
        sum += tmp->val;
        TAILQ_REMOVE(q, tmp, field);
        free(tmp);
    }
    free(q);
    return sum;
}

int dfs_sum(struct TreeNode*root, int prevSum)
{
    if (root == NULL) {
        return prevSum;
    }

    int sum = root->val + prevSum * 10;
    if (root->left == NULL && root->right == NULL) {
        return sum;
    } else if (root->left != NULL && root->right == NULL)
    {
        return dfs_sum(root->left, sum);
    } else if (root->left == NULL && root->right != NULL)
    {
        return dfs_sum(root->right, sum);
    } else {
        return dfs_sum(root->left, sum) + dfs_sum(root->right, sum);
    }
}

int sumNumbers_02(struct TreeNode *root)
{
    return dfs_sum(root, 0);
}

int a[] = {1,5,1,null,null,null,6};
int main()
{
    int sum = 131;
    struct TreeNode *root = LayerArrayToTree(a, sizeof(a)/sizeof(int));
    assert(sumNumbers_02(root) == sum);
    printf("test is passed.\n");
    return 0;
}