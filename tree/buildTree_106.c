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
struct TreeNode* buildTree(int* inorder, int inorderSize, int* postorder, int postorderSize) {
    // post [....left_r, ... right_r, root]
    // inorder [ ..left_r..., root, ...right_r...]
    
    assert(inorderSize == postorderSize);
    if (inorderSize == 0 || inorder == NULL || postorder == NULL) {
        return NULL;
    }
    int root_v = postorder[postorderSize-1];
    struct TreeNode *root_node = MallocTreeNode(root_v);
    if (inorderSize == 1) {
        return root_node;
    }

    int inorder_root_idx = 0;
    for (; inorder_root_idx < inorderSize; inorder_root_idx++) {
        if (inorder[inorder_root_idx] == root_v) {
            break;
        }
    }
    assert(inorder_root_idx < inorderSize);

    int left_tree_size = inorder_root_idx;
    int right_tree_size = inorderSize - left_tree_size - 1;

    if (left_tree_size > 0) {
        root_node->left = buildTree(inorder, left_tree_size, postorder, left_tree_size);
    }
    if (right_tree_size > 0) {
        root_node->right = buildTree(&inorder[inorder_root_idx+1], right_tree_size, &postorder[left_tree_size], right_tree_size);
    }
    return root_node;
}

int inorder[] = {9,3,15,20,7};
int postorder[] = {9,15,7,20,3};

int main(void)
{
    struct TreeNode *root = buildTree(inorder, sizeof(inorder)/sizeof(int), postorder, sizeof(postorder)/sizeof(int));
    return 0;
}