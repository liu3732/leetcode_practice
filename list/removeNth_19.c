#include <list.h>
#include <stdlib.h>

int GetListCnt(struct ListNode *head)
{
    int cnt = 0;
    while (head != NULL) {
        cnt++;
        head = head->next;
    }
    return cnt;
}

void GetPrevAndNode(struct ListNode *head, int xth, struct ListNode **prev, struct ListNode **node)
{
    *prev = NULL;
    *node = head;

    while ((*node) != NULL && --xth > 0) {
        *prev = *node;
        *node = (*node)->next;
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
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    int len = GetListCnt(head);
    int order = len - n + 1;

    struct ListNode *prev, *node;
    GetPrevAndNode(head, order, &prev, &node);
    
    if (node == NULL) {
        return head;
    }
    if (prev == NULL) {
        struct ListNode *n_h =head->next;
        free(head);
        return n_h;
    }

    prev->next = node->next;
    free(node);
    return head;    
}

int g_a[] = {1,2};

int main()
{
    struct ListNode *h = InitListNode(g_a, sizeof(g_a)/sizeof(int));
    h = removeNthFromEnd(h, 2);
    PrintListNode(h);
    FreeList(h);
}