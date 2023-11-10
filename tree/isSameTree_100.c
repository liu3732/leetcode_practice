/*
 * @Author: liuxiaoxiang liu3732@gmail.com
 * @Date: 2023-11-07 21:10:52
 * @LastEditors: liuxiaoxiang liu3732@gmail.com
 * @LastEditTime: 2023-11-07 21:26:16
 * @FilePath: \leetcode_practice\isSameTree_100.c
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <stdbool.h>
#include "bin_tree.h"
#include <stdlib.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
bool isSameTree(struct TreeNode* p, struct TreeNode* q) {
    if (p == NULL && q == NULL) {
        return true;
    }
    if (p == NULL && q != NULL || p != NULL && q == NULL) {
        return false;
    }

    if(p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right)) {
        return true;
    }
    return false;
}