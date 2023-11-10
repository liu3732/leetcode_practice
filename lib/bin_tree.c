/*
 * @Author: liu3732 liu3732@gmail.com
 * @Date: 2023-10-26 09:44:18
 * @LastEditors: liu3732 liu3732@gmail.com
 * @LastEditTime: 2023-11-10 16:00:11
 * @FilePath: \leetcode_practice\lib\bin_tree.c
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include <bin_tree.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <stdint.h>
#include <assert.h>

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
    if (*p2num_size == 0 || *p2a == NULL) {
        return NULL;
    }
    
    if (**p2a == NULL_NODE) {
        *p2num_size--;
        *p2a += 1;
        return NULL;
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

struct entry {
    struct TreeNode *p;
    TAILQ_ENTRY(entry) entries;
};
TAILQ_HEAD(t_queue, entry);

uint32_t GetQueueLen(struct t_queue *q_head)
{
    struct entry *dumy;
    int len = 0;
    TAILQ_FOREACH(dumy, q_head, entries)
    {
        len++;
    }
    return len;
}

struct entry *MallocQueueEntry(int v)
{
    struct entry* elem = (struct entry*)malloc(sizeof(struct entry));
    elem->p = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    elem->p->val = v;
    elem->p->left = NULL;
    elem->p->right = NULL;
    return elem;
}

/**
 * @description: 
 * @param {int} *a
 * @param {unsigned int} num_size
 * @return {*}
 */
struct TreeNode *LayerArrayToTree(int **p2a, unsigned int *num_size)
{
    int *a = *p2a;
    if (a == NULL || *num_size == 0) {
        return NULL;
    }
    int i = 0;
    struct t_queue q_head;
    TAILQ_INIT(&q_head);
    
    struct entry *elem = MallocQueueEntry(a[i++]);
    struct TreeNode *root = elem->p;
    TAILQ_INSERT_HEAD(&q_head, elem, entries);

    uint32_t len = GetQueueLen(&q_head);
    while (!TAILQ_EMPTY(&q_head)) {
        while(len > 0) {
            struct entry *head = TAILQ_LAST(&q_head, t_queue);
            TAILQ_REMOVE(&q_head, head, entries);
            
            if(head->p->val == NULL_NODE) {
                free(head);
                continue;
            }
            if(i >= *num_size) {
                free(head);
                return root;
            }
            elem = MallocQueueEntry(a[i++]);
            head->p->left = elem->p;
            TAILQ_INSERT_HEAD(&q_head, elem, entries);

            if(i >= *num_size) {
                free(head);
                return root;
            }
            elem = MallocQueueEntry(a[i++]);
            head->p->right = elem->p;
            TAILQ_INSERT_HEAD(&q_head, elem, entries);
            free(head);
            len--;
        }
        len = GetQueueLen(&q_head);
    }
    return root;
}