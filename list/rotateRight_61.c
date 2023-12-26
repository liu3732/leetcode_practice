#include <stdlib.h>
#include <list.h>

int getListLen(struct ListNode *head, struct ListNode **end)
{
    *end = head;
    if(*end == NULL) {
        return 0;
    }
    int n = 1;
    while((*end)->next != NULL) {
        n++;
        (*end) = (*end)->next;
    }
    return n;
}

void getXthNode(struct ListNode *head, int xth, struct ListNode **prev, struct ListNode **last)
{
    *prev = NULL;
    *last = head;
    while(--xth) {
        *prev = *last;
        *last = (*last)->next;
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
struct ListNode* rotateRight(struct ListNode* head, int k) {
    struct ListNode *end;
    int n = getListLen(head, &end);
    if (n == 0) {
        return NULL;
    }
    k = k < n ? k : k%n;
    if (k == 0) {
        return head;
    }

    struct ListNode *prev, *last;
    getXthNode(head, n - k + 1, &prev, &last);
    end->next = head;
    prev->next =NULL;
    
    return last;
}

int g_a[] = {0,1,2};
int main()
{
    struct ListNode *h = InitListNode(g_a, sizeof(g_a)/sizeof(int));
    h = rotateRight(h, 3);
    PrintListNode(h);
    FreeList(h);
}