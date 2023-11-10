#include "bin_tree.h"

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* invertTree(struct TreeNode* root) {
    if(root == NULL) {
        return NULL;
    }
    
    struct TreeNode* invertLeft = invertTree(root->left);
    struct TreeNode* invertRight = invertTree(root->right);
    root->left = invertRight;
    root->right = invertLeft;
    
    return root;
}