#include "bin_tree.h"
#include "stdbool.h"
#include "assert.h"
#include "stdlib.h"
#include "stdio.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool hasPathSum(struct TreeNode* root, int targetSum) {
    if (root == NULL) {
        return false;
    }

    if (root->left == NULL && root->right == NULL) {
        return root->val == targetSum;
    }

    bool ret = false;
    if (root->left != NULL) {
        ret |= hasPathSum(root->left, targetSum-root->val);
    }
    if (root->right != NULL) {
        ret |= hasPathSum(root->right, targetSum-root->val);
    }
    return ret;
}

int a[] = {5,4,8,11,null,13,4,7,2,null,null,null,1};

int main(void)
{
    int target_sum = 22;
    struct TreeNode *root = LayerArrayToTree(a, sizeof(a)/sizeof(int));
    assert(hasPathSum(root, target_sum) == true);
    printf("test passed!\n");
    return 0;
}