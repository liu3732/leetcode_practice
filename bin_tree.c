/*
 * @Author: liu3732 liu3732@gmail.com
 * @Date: 2023-10-26 09:44:18
 * @LastEditors: liu3732 liu3732@gmail.com
 * @LastEditTime: 2023-10-26 16:08:13
 * @FilePath: \leetcode_practice\bin_tree.c
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include <bin_tree.h>
#include <stdlib.h>

struct TreeNode *AllocTreeNode(int v)
{
    struct TreeNode *ret = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    ret->left = NULL;
    ret->right = NULL;
    ret->val = v;
}

/**
 * @description: generate Tree from a array. the array is traversed by pre-order.
 * @param {int} **a
 * @param {unsigned int} num_size
 * @return {*}
 */
struct TreeNode *PreArrayToTree(int **p2a, unsigned int *p2num_size)
{
    if (*p2num_size == 0 || **p2a == NULL_NODE) {
        return NULL;
    }

    if(*p2num_size == 1) {
        struct TreeNode *root = AllocTreeNode(**p2a);
        root->left = NULL;
        root->right = NULL;
        *p2num_size--;
        return root;
    }

    struct TreeNode *root = AllocTreeNode(**p2a);
    
    *p2a += 1;
    *p2num_size -= 1;
    root->left = PreArrayToTree(p2a, p2num_size);
    root->right = PreArrayToTree(p2a, p2num_size);

    return root;
}

/**
 * @description: 
 * @param {int} *a
 * @param {unsigned int} num_size
 * @return {*}
 */
struct TreeNode *PostArrayToTree(int **p2a, unsigned int *num_size)
{
    return NULL;
}

/**
 * @description: 
 * @param {int} *a
 * @param {unsigned int} num_size
 * @return {*}
 */
struct TreeNode *LayerArrayToTree(int **p2a, unsigned int *num_size)
{
    return NULL;
}