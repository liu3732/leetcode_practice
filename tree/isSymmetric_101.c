/*
 * @Author: liu3732 liu3732@gmail.com
 * @Date: 2023-11-10 10:51:46
 * @LastEditors: liu3732 liu3732@gmail.com
 * @LastEditTime: 2023-11-10 16:00:44
 * @FilePath: \leetcode_practice\tree\isSymmetric_101.c
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include "bin_tree.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

bool isSameMirror(struct TreeNode *left, struct TreeNode *right)
{

    if (left == NULL && right == NULL) {
        return true;
    } else if (left == NULL && right != NULL || left != NULL && right == NULL)
    {
        return false;
    }
    
    if (left->val == right->val &&
        isSameMirror(left->right, right->left) &&
        isSameMirror(left->left, right->right)) {
        return true;
    } else {
        return false;
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
bool isSymmetric(struct TreeNode* root) {
    if(root == NULL) {
        return true;
    }
    return isSameMirror(root->left, root->right);
}

int a[] = {1,2,2,3,4,4,3};

int main()
{
    int len = sizeof(a)/sizeof(int);
    int *p = (int *)malloc(sizeof(a));
    for (int i = 0; i < len; i++) {
        p[i] = a[i];
    }

    struct TreeNode* root = LayerArrayToTree(&p, &len);
    assert(isSymmetric(root) == true);
    printf("the test has been passed.\n");
}