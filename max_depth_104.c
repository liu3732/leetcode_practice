/*
 * @Author: liu3732 liu3732@gmail.com
 * @Date: 2023-10-26 09:42:55
 * @LastEditors: liu3732 liu3732@gmail.com
 * @LastEditTime: 2023-10-26 17:39:47
 * @FilePath: \leetcode_practice\max_depth_104.c
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#include <bin_tree.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

static inline int max_int(int a, int b)
{
    return a > b ? a : b;
}

int maxDepth(struct TreeNode *root)
{
    if (root == NULL) {
        return 0;
    }
    return (max_int(maxDepth(root->left), maxDepth(root->right)) + 1);
}


int main()
{
    int a[] = {3, NULL_NODE, NULL_NODE};
    int len = sizeof(a)/sizeof(int);
    
    int *pa = a;
    struct TreeNode *root = PreArrayToTree(&pa, &len);
    assert(maxDepth(root) == 1);
    printf("test has been passed.\n");
    return 0;
}