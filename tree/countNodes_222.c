#include "bin_tree.h"
#include <assert.h>
#include <stdio.h>

void countNums(struct TreeNode *root, int *preNum)
{
    if (root == NULL) {
        return;
    }

    countNums(root->left, preNum);
    *preNum += 1;
    countNums(root->right, preNum);
}
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int countNodes(struct TreeNode* root) {
    int num = 0;
    countNums(root, &num);

    return num;
}

int a1[] = {1, 2, 3, 4, 5, 6};
int *a2 = NULL;

int a3[] = {1};

int main()
{
    struct TreeNode* root = LayerArrayToTree(a1, sizeof(a1)/sizeof(int));
    assert(countNodes(root) == 6);
    FreeTree(root);

    root = LayerArrayToTree(a2, 0);
    assert(countNodes(root) == 0);
    FreeTree(root);

    root = LayerArrayToTree(a3, sizeof(a3)/sizeof(int));
    assert(countNodes(root) == 1);
    FreeTree(root);

    printf("the test has been passed.\n");
}