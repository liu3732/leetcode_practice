#include <list.h>
#include <stdlib.h>

void reverse(struct ListNode *prev, struct ListNode *left, struct ListNode *right)
{
    struct ListNode *right_nxt = right->next;
    struct ListNode *p = right_nxt;
    struct ListNode *c = left;

    while (c != right_nxt) {
        struct ListNode *nxt_c = c->next;
        c->next = p;

        p = c;
        c = nxt_c;
    }
    if (prev) {
        prev->next = right;
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
struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    if (k == 1) {
        return head;
    }

    struct ListNode *left = head;
    struct ListNode *prev = NULL;
    struct ListNode *right = GetXthNode(left, k-1);
    
    struct ListNode *ret = right;

    while (right != NULL) {
        reverse(prev, left, right);

        prev = left;
        left = left->next;
        right = GetXthNode(left, k-1);
    }

    return ret;
}

int g_a[] = {1, 2, 3, 4, 5};
int main()
{
    struct ListNode *n = InitListNode(g_a, sizeof(g_a)/sizeof(int));
    struct ListNode *p = reverseKGroup(n, 5);
    PrintListNode(p);
    FreeList(p);
}