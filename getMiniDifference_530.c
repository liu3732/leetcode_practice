#include "bin_tree.h"
#include <assert.h>
#include <stdlib.h>
#include "limits.h"
#include "stdio.h"

int get_right_most(struct TreeNode *node)
{
    struct TreeNode *p = node;
    while (p->right != NULL) {
        p = p->right;
    }
    return p->val;
}

int get_left_most(struct TreeNode *node)
{
    struct TreeNode *p = node;
    while (p->left != NULL) {
        p = p->left;
    }
    return p->val;
}

void update_min_dfs(struct TreeNode* root, int *min_ptr)
{
    if (root == NULL || (root->left == NULL && root->right == NULL)) {
        return;
    }

    int left_min = INT_MAX;
    int right_min = INT_MAX;

    if(root->left != NULL) {
        left_min = root->val - get_right_most(root->left);
        if (left_min < *min_ptr) {
            *min_ptr = left_min;
        }
    }
    if(root->right != NULL) {
        right_min = get_left_most(root->right) - root->val;
        if (right_min < *min_ptr) {
            *min_ptr = right_min;
        }
    }
    update_min_dfs(root->left, min_ptr);
    update_min_dfs(root->right, min_ptr);
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
int getMinimumDifference(struct TreeNode* root)
{
    int ret_min = INT_MAX;

    update_min_dfs(root, &ret_min);
    return ret_min;
}


int main()
{
    int a[] = {4, 2, 1, NULL_NODE, NULL_NODE, 3, NULL_NODE, NULL_NODE, 6, NULL_NODE, NULL_NODE};
    //int a[] = {1, 0, NULL_NODE, NULL_NODE, 48, 12, NULL_NODE, NULL_NODE, 49, NULL_NODE, NULL_NODE};
    int len = sizeof(a)/sizeof(int);
    
    int *pa = a;
    struct TreeNode *root = PreArrayToTree(&pa, &len);

    assert(1 == getMinimumDifference(root));
    printf("the test has been passed.\n");
}