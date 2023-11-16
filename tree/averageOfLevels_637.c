#include "bin_tree.h"
#include <stdlib.h>
#include <queue.h>
#include <stdio.h>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
double* averageOfLevels(struct TreeNode* root, int* returnSize) {
    double *retAverages = NULL;
    *returnSize = 0;

    if (root == NULL) {
        return retAverages;
    }
    struct queue* fifo = CreateQueue(10000);
    int layerNum = 1;

    EnQueue(fifo, (QUEUE_TYPE)root);
    int len = GetLen(fifo);
    
    while (!IsEmpty(fifo)) {
        retAverages = (double *)realloc(retAverages, layerNum*sizeof(double));
        int r = layerNum - 1;
        *returnSize = layerNum;
        retAverages[r] = 0;

        for (int i = 0; i < len; i++) {
            struct TreeNode*tmp = NULL;
            PopQueue(fifo, (QUEUE_TYPE *)&tmp);
            retAverages[r] += tmp->val;

            if(tmp->left != NULL) {
                EnQueue(fifo, (QUEUE_TYPE)tmp->left);
            }
            if(tmp->right != NULL) {
                EnQueue(fifo, (QUEUE_TYPE)tmp->right);
            }
        }
        retAverages[r] = retAverages[r]/len;
        len = GetLen(fifo);
        layerNum++;
    }
    return retAverages;
}

int a[] = {3,9,20,15,7};

int main()
{
    struct TreeNode *root = LayerArrayToTree(a, sizeof(a)/sizeof(int));
    
    double *retAverage = NULL;
    int retSize = 0;

    retAverage = averageOfLevels(root, &retSize);
    for (int i = 0; i < retSize; i++) {
        printf("%f\n", retAverage[i]);
    }
    free(retAverage);
    FreeTree(root);
    return 0;
}