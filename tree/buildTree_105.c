#include "bin_tree.h"
#include <assert.h>
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
struct TreeNode* buildTree(int* preorder, int preorderSize, int* inorder, int inorderSize) {
    assert(preorderSize == inorderSize);
    
    if (preorderSize == 0 || preorder == NULL || inorder == NULL) {
        return NULL;
    }

    // 1. get root from preorder[0]
    //  pre [root, left_root, .... , right_root, ....]
    //  in [... left_root ..., root, ... right_root ... ]
    int root = preorder[0];
    struct TreeNode *rt = MallocTreeNode(root);
    if (preorderSize == 1) {
        return rt;
    }

    int r_id = 0;
    for (; r_id < inorderSize; r_id++) {
        if (root == inorder[r_id]) {
            break;
        }
    }
    assert(r_id < inorderSize);

    // 2. get l_sz + r_sz
    int l_sz = r_id;
    int r_sz = inorderSize - l_sz - 1;

    if (l_sz > 0) {
        int start_id = (r_id == 0) ? 1 : 0;
        struct TreeNode *l_rt = buildTree(&preorder[1], l_sz, &inorder[start_id], l_sz);
        rt->left = l_rt;
    }
    if (r_sz > 0) {
        struct TreeNode *r_rt = buildTree(&preorder[1+l_sz], r_sz, &inorder[r_id+1], r_sz);
        rt->right = r_rt;
    }
    return rt;    
}

int preorder[] = {3,9,20,15,7};
int inorder[] = {9,3,15,20,7};
int main()
{
    struct TreeNode *root = buildTree(preorder, sizeof(preorder)/sizeof(int), inorder, sizeof(inorder)/sizeof(int));
    assert(root != NULL);
    assert(root->val = 3);
    return 0;
}