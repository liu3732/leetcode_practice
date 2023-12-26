#include <stdio.h>
#include <list.h>
#include <stdlib.h>
#include <assert.h>

struct ListNode *getPrev(struct ListNode *head, struct ListNode *node)
{
    if (head == node) {
        return NULL;
    }

    while(head->next != node) {
        head = head->next;
    }
    return head;
}

void reverseList(struct ListNode *p_head, struct ListNode *head, struct ListNode *tail)
{
    struct ListNode *nxt_tail = tail->next;
    struct ListNode *prev = nxt_tail;
    struct ListNode *cur = head;

    while(cur != nxt_tail) {
        struct ListNode *nxt_cur = cur->next;
        cur->next = prev;
        
        prev = cur;
        cur = nxt_cur;
    }
    if (p_head) {
        p_head->next = tail;
    }
    return;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* reverseBetween(struct ListNode* head, int left, int right) {
    assert(left <= right);
    if (left == right) {
        return head;
    }
    if (head == NULL) {
        return NULL;
    }

    struct ListNode *l = GetXthNode(head, left-1);
    struct ListNode *r = GetXthNode(head, right-1);

    struct ListNode *prevLeft = getPrev(head, l);
    if (prevLeft == NULL) {
        reverseList(prevLeft, l, r);
        return r;
    } else {
        reverseList(prevLeft, l, r);
        return head;
    }
}

int a[] = {1, 2, 5};
int main()
{
    struct ListNode *t = InitListNode(a, sizeof(a)/sizeof(int));
    struct ListNode *h = reverseBetween(t, 1, 2);
    PrintListNode(h);
    FreeList(h);
}