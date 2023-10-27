#include "queue.h"
#include "bin_tree.h"
#include "stdio.h"


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* rightSideView(struct TreeNode* root, int* returnSize) {
    static int tmp_a[100];
    *returnSize = 0;
    if (root == NULL) {
        return NULL;
    }

    struct queue *q_head = CreateQueue(100);
    struct queue *q_tmp = CreateQueue(100);
    

    EnQueue(q_head, (QUEUE_TYPE)root);
    while(!IsEmpty(q_head)) {
        QUEUE_TYPE right_v = NULL;
        while (!IsEmpty(q_head)) {
            PopQueue(q_head, &right_v);
            EnQueue(q_tmp, (QUEUE_TYPE)(((struct TreeNode *)right_v)->left));
            EnQueue(q_tmp, (QUEUE_TYPE)(((struct TreeNode *)right_v)->right));
        }
        tmp_a[*returnSize] = ((struct TreeNode *)right_v)->val;
        *returnSize += 1;
        right_v = NULL;
        while (!IsEmpty(q_tmp)) {
            PopQueue(q_tmp, &right_v);
            EnQueue(q_head, right_v);
        }
    }
    FreeQueue(q_head);
    FreeQueue(q_tmp);
    return (int *)tmp_a;
}

int main()
{
    //int a[] = {1, 2, NULL_NODE, 5, NULL_NODE, NULL_NODE, 3, NULL_NODE, 4, NULL_NODE, NULL_NODE};
    //int a[] = {1, NULL_NODE, 3, NULL_NODE, NULL_NODE};
    int *a = NULL;
    int len = sizeof(a)/sizeof(int);
    
    int *pa = a;
    struct TreeNode *root = PreArrayToTree(&pa, &len);

    int ret_size = 0;
    int *ret_a = rightSideView(root, &ret_size);

    for (int i = 0; i < ret_size; i++) {
        printf("%d ", ret_a[i]);
    }
    printf("\n");
    return 0;
}