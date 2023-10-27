/*
 * @Author: liu3732 liu3732@gmail.com
 * @Date: 2023-10-26 16:40:57
 * @LastEditors: liu3732 liu3732@gmail.com
 * @LastEditTime: 2023-10-27 09:38:35
 * @FilePath: \leetcode_practice\queue.c
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include <queue.h>
#include <stdlib.h>
#include <stdint.h>

struct queue *CreateQueue(uint32_t max_len)
{
    struct queue *ret = (struct queue *)malloc(sizeof(struct queue));
    ret->a = (QUEUE_TYPE *)malloc((max_len+1) * sizeof(QUEUE_TYPE));
    ret->max_len = max_len;
    ret->tail = 0;
    ret->head = 0;
    return ret;
}

int GetNextQueuePtr(int max_len, int ptr)
{
    return (ptr + 1)%max_len;
}

bool IsEmpty(struct queue *q_head)
{
    return q_head->tail == q_head->head;
}

bool IsFull(struct queue *q_head)
{
    return GetNextQueuePtr(q_head->max_len, q_head->tail) == q_head->head;
}

bool EnQueue(struct queue *q_head, QUEUE_TYPE v)
{
    if (IsFull(q_head)) {
        return false;
    }
    if (v == NULL) {
        return false;
    }

    q_head->a[q_head->tail] = v;
    q_head->tail = GetNextQueuePtr(q_head->max_len, q_head->tail);
    return true;
}

bool PopQueue(struct queue *q_head, QUEUE_TYPE *out)
{
    if (IsEmpty(q_head)) {
        return false;
    }
    *out = q_head->a[q_head->head];
    q_head->head = GetNextQueuePtr(q_head->max_len, q_head->head);
    return true;
}

void FreeQueue(struct queue *q_head)
{
    free(q_head->a);
}
