#include "bin_tree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

bool traverseValidBST(struct TreeNode *root, int *min, int *max)
{
    if (root == NULL) {
        *min = 0;
        *max = 0;
        return true;
    }

    bool isRightValid = false, isLeftValid = false;
    int minRight, minLeft, maxRight, maxLeft;

    if (root->left == NULL && root->right == NULL) {
        *min = root->val;
        *max = root->val;
        return true;
    } else if (root->left == NULL && root->right != NULL)
    {
        isRightValid = traverseValidBST(root->right, &minRight, &maxRight);
        if(!isRightValid) {
            return false;
        }
        if (root->val < minRight) {
            *min = root->val;
            *max = maxRight;
            return true;
        } else {
            return false;
        }

    } else if (root->left != NULL && root->right == NULL)
    {
        /* code */
        isLeftValid = traverseValidBST(root->left, &minLeft, &maxLeft);
        if(!isLeftValid) {
            return false;
        }
        if(root->val > maxLeft) {
            *min = minLeft;
            *max = root->val;
            return true;
        } else {
            return false;
        }
        return true;
    } else {
        isLeftValid = traverseValidBST(root->left, &minLeft, &maxLeft);
        isRightValid = traverseValidBST(root->right, &minRight, &maxRight);
        if(!isLeftValid || !isRightValid) {
            return false;
        }
        if (root->val > maxLeft && root->val < minRight) {
            *min = minLeft;
            *max = maxRight;
            return true;
        } else {
            return false;
        }
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
bool isValidBST(struct TreeNode* root) {
    int min = 0;
    int max = 0;

    return traverseValidBST(root, &min, &max);
}


int a[] = {5,1,4,null,null,3,6};

int main()
{
    struct TreeNode *root = LayerArrayToTree(a, sizeof(a)/sizeof(int));
    assert(isValidBST(root) == false);
    FreeTree(root);
    printf("the test has been passed.\n");
    return 0;
}