/*
 * @Author: liu3732 liu3732@gmail.com
 * @Date: 2023-10-26 16:34:31
 * @LastEditors: liu3732 liu3732@gmail.com
 * @LastEditTime: 2023-10-27 09:39:32
 * @FilePath: \leetcode_practice\include\queue.h
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */
#ifndef __QUEUE__
#define __QUEUE__

#include <stdbool.h>
#include <stdint.h>

typedef void * QUEUE_TYPE;
struct queue {
    QUEUE_TYPE *a;
    uint32_t max_len;
    uint32_t head;
    uint32_t tail;
};

struct queue *CreateQueue(uint32_t max_len);
bool IsEmpty(struct queue *q_head);
bool EnQueue(struct queue *q_head, QUEUE_TYPE v);
bool PopQueue(struct queue *q_head, QUEUE_TYPE *out);
void FreeQueue(struct queue *q_head);

#endif