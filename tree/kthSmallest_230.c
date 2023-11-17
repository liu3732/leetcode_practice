#include "bin_tree.h"
#include "stdlib.h"
#include <assert.h>
#include <stdio.h>

int *inOrderTraverse(struct TreeNode* root, int *size)
{
    int *left_a = NULL;
    int left_s = 0;

    int *right_a = NULL;
    int right_s = 0;

    int *return_a = NULL;
    *size = 0;

    if (root == NULL) {
        return NULL;
    }

    left_a = inOrderTraverse(root->left, &left_s);
    right_a = inOrderTraverse(root->right, &right_s);

    *size = left_s + right_s + 1;
    return_a = (int *)malloc((*size)*sizeof(int));

    int ti = 0;
    int si = 0;

    if (left_a != NULL) {
        for (; si < left_s ; si++, ti++) {
            return_a[ti] = left_a[si];
        }
        free(left_a);
    }    


    return_a[ti++] = root->val;

    if (right_a != NULL) {
        for (si = 0; si < right_s; si++, ti++) {
            return_a[ti] = right_a[si];
        }
        free(right_a);
    }


    return return_a;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
int kthSmallest(struct TreeNode* root, int k) {
    int len = 0;
    int *a = inOrderTraverse(root, &len);

    int ret = a[k-1];
    free(a);
    return ret;
}

int a[] = {5,3,6,2,4,null,null,1};
int main()
{
    struct TreeNode *root = LayerArrayToTree(a, sizeof(a)/sizeof(int));
    assert(kthSmallest(root, 3) ==  3);
    printf("test has been passed.\n");
    FreeTree(root);
}