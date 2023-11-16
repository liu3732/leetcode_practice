#include "bin_tree.h"
#include <stdlib.h>
#include <sys/queue.h>
#include <assert.h>
#include <stdio.h>

struct elem_t {
    struct TreeNode *node;
    TAILQ_ENTRY(elem_t) entry;
};

struct fifo_t {
    int len;
    TAILQ_HEAD(tailq_t, elem_t) queue;
};

void initFifo(struct fifo_t *fifo)
{
    fifo->len = 0;
    TAILQ_INIT(&fifo->queue); 
}

void enFifo(struct fifo_t *fifo, struct TreeNode *v)
{
    fifo->len++;
    struct elem_t *elem = (struct elem_t *)malloc(sizeof(struct elem_t));
    elem->node = v;
    TAILQ_INSERT_HEAD(&fifo->queue, elem, entry);
}

struct TreeNode *popFifo(struct fifo_t *fifo)
{
    assert(!TAILQ_EMPTY(&fifo->queue) && fifo->len > 0);
    struct elem_t *elem = TAILQ_LAST(&fifo->queue, tailq_t);
    struct TreeNode * ret = elem->node;
    
    TAILQ_REMOVE(&fifo->queue, elem, entry);
    free(elem);
    fifo->len--;

    return ret;
}

void freeFifo(struct fifo_t *fifo)
{
    while(!TAILQ_EMPTY(&fifo->queue)) {
        struct elem_t *elem = TAILQ_LAST(&fifo->queue, tailq_t);
        TAILQ_REMOVE(&fifo->queue, elem, entry);
        free(elem);
        fifo->len--;
    }
    return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int** levelOrder(struct TreeNode* root, int* returnSize, int** returnColumnSizes) {
    if(root == NULL) {
        *returnSize = 0;
        *returnColumnSizes = NULL;
        return NULL;
    }

    int layerNum = 1;
    struct fifo_t myFifo;

    initFifo(&myFifo);
    enFifo(&myFifo, root);
    int len = myFifo.len;

    int **returnArray = NULL;
    *returnColumnSizes = NULL;

    while(!TAILQ_EMPTY(&myFifo.queue))
    {
        *returnSize = layerNum;
        returnArray = (int **) realloc(returnArray, layerNum*sizeof(int *));
        *returnColumnSizes = (int *)realloc(*returnColumnSizes, layerNum*sizeof(int));

        int r = layerNum-1;
        returnArray[r] = (int *)malloc(sizeof(int)*len);
        (*returnColumnSizes)[r] = len;

        for (int c = 0; c < len; c++) {
            struct TreeNode *tmp = popFifo(&myFifo);
            returnArray[r][c] = tmp->val;
            if(tmp->left != NULL) {
                enFifo(&myFifo, tmp->left);
            }
            if(tmp->right != NULL) {
                enFifo(&myFifo, tmp->right);
            }
        }
        layerNum++;
        len = myFifo.len;
    }
    freeFifo(&myFifo);
    return returnArray;
}

int a[] = {1};
int main(void)
{
    struct TreeNode *root = LayerArrayToTree(NULL, 0);

    int rowSize = 0;
    int *colSizes = NULL;
    int **retArray = levelOrder(root, &rowSize, &colSizes);

    for (int r = 0; r < rowSize; r++) {
        for(int c = 0; c < colSizes[r]; c++) {
            printf("%d ", retArray[r][c]);
        }
        printf("\n");
        free(retArray[r]);
    }
    free(retArray);
    free(colSizes);
    printf("the test has been passed.\n");
}