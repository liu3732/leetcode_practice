#include "list.h"
#include "stdlib.h"
#include "stdio.h"

struct ListNode *InitListNode(int *array, int arraySize)
{
    struct ListNode *listHead = NULL, *prev = NULL;
    
    if (arraySize <= 0) {
        return NULL;
    }

    listHead = (struct ListNode *)malloc(sizeof(struct ListNode));
    listHead->val = array[0];
    listHead->next = NULL;
    prev = listHead;

    for (int i = 1; i < arraySize; i++) {
        struct ListNode *tmp;
        tmp = (struct ListNode *)malloc(sizeof(struct ListNode));
        tmp->val = array[i];
        tmp->next = NULL;
        prev->next = tmp;
        prev = prev->next;
    }
    return listHead;
}

void PrintListNode(struct ListNode *listHead)
{
    while (listHead != NULL)
    {
        printf("%d",listHead->val);
        listHead->next == NULL ? printf("\n") : printf(" ");
        listHead = listHead->next;
    }
}

struct ListNode *GetXthNode(struct ListNode *listNode, int xth)
{
    struct ListNode *cur = listNode;
    int cnt = 0;
    while (cur != NULL) {
        if (cnt == xth) {
            return cur;
        }
        cnt++;
        cur = cur->next;
    }
    return NULL;
}

void InsertListTail(struct ListNode **listHead, struct ListNode *new)
{
    if (*listHead == NULL) {
        *listHead = new;
        new->next = NULL;
        return;
    }

    struct ListNode *prev = *listHead;

    while (prev->next != NULL) {
        prev = prev->next;
    }
    prev->next = new;
    new->next = NULL;
}
