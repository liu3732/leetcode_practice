#include "bin_tree.h"
#include <stdlib.h>
#include <sys/queue.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>

struct elem_t {
    struct TreeNode *node;
    TAILQ_ENTRY(elem_t) entry;
};

TAILQ_HEAD(queue_t, elem_t);


int GetLen(struct queue_t *q_head)
{
    struct elem_t *tmp = NULL;
    int ret_len = 0;
    TAILQ_FOREACH(tmp, q_head, entry) {
        ret_len++;
    }
    return ret_len;
}

void PushQ(struct queue_t *q_head, struct TreeNode *node)
{
    if (node == NULL) {
        return;
    }

    struct elem_t *elem = (struct elem_t *)malloc(sizeof(struct elem_t));
    elem->node = node;
    TAILQ_INSERT_HEAD(q_head, elem, entry);
}

struct TreeNode *PopHeadQ(struct queue_t *q_head)
{
    assert(q_head != NULL && !TAILQ_EMPTY(q_head));

    struct elem_t *elem = TAILQ_FIRST(q_head);
    TAILQ_REMOVE(q_head, elem, entry);
    
    struct TreeNode *ret = elem->node;
    free(elem);
    return ret;
}

struct TreeNode *PopTailQ(struct queue_t *q_head)
{
    assert(q_head != NULL && !TAILQ_EMPTY(q_head));

    struct elem_t *elem = TAILQ_LAST(q_head, queue_t);
    TAILQ_REMOVE(q_head, elem, entry);
    
    struct TreeNode *ret = elem->node;
    free(elem);
    return ret;
}

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */
/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** zigzagLevelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    int **retArray = NULL;
    *returnSize = 0;
    *returnColumnSizes = NULL;

    if (root == NULL) {
        return retArray;
    }

    int layerNum = 1;
    struct queue_t tailq;
    TAILQ_INIT(&tailq);;

    PushQ(&tailq, root);
    int len = GetLen(&tailq);

    while(!TAILQ_EMPTY(&tailq)) {
        *returnSize = layerNum;
        *returnColumnSizes = (int *)realloc(*returnColumnSizes, layerNum*sizeof(int));
        int r = layerNum-1;
        (*returnColumnSizes)[r] = len;
        retArray = (int **)realloc(retArray, layerNum*sizeof(int *));
        retArray[r] = (int *)malloc(len*sizeof(int));
        
        int zigZag = layerNum%2;
        struct elem_t *elem = NULL;
        int c = 0;
        if (zigZag) {
            TAILQ_FOREACH_REVERSE(elem, &tailq, queue_t, entry)
            {
                retArray[r][c] = elem->node->val;
                c++;
            }
        } else {
            TAILQ_FOREACH(elem, &tailq, entry)
            {
                retArray[r][c] = elem->node->val;
                c++;
            }
        }

        for (int c = 0; c < len; c++) {
            struct TreeNode *tmp = PopTailQ(&tailq);
            PushQ(&tailq, tmp->left);
            PushQ(&tailq, tmp->right);
        }
        
        layerNum++;
        len = GetLen(&tailq);
    }
    return retArray;
}

int a[] = {3,9,20,null,null,15,7};
int main()
{
    struct TreeNode *root = LayerArrayToTree(a, sizeof(a)/sizeof(int));

    int **retArray = NULL;
    int *retColSizes = NULL;
    int retRowSize = 0;

    retArray = zigzagLevelOrder(root, &retRowSize, &retColSizes);
    for (int r = 0; r < retRowSize; r++)
    {
        for(int c = 0; c < retColSizes[r]; c++) {
            printf("%d ", retArray[r][c]);
        }
        free(retArray[r]);
        printf("\n");
    }
    free(retArray);
    free(retColSizes);
    FreeTree(root);

}