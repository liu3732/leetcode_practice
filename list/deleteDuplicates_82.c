#include <list.h>
#include <stdbool.h>
#include <stdlib.h>

bool deleteDupsOnce(struct ListNode **head, struct ListNode **next)
{
    if (*head == NULL) {
        return false;
    }
    struct ListNode *prev = NULL;
    struct ListNode *cur = *head;
    struct ListNode *nxt = (*head)->next;

    while (nxt != NULL)
    {
        if(cur->val == nxt->val) {
            while(nxt != NULL && cur->val == nxt->val) {
                *next = nxt->next;
                free(nxt);
                nxt = (*next);
            }
            free(cur);
            if(prev) {
                prev->next = (*next);
            } else {
                *head = (*next);
            }
            return true;
        } else {
            prev = cur;
            cur = nxt;
            nxt = nxt->next;
        }
    }
    return false;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* deleteDuplicates(struct ListNode* head) {
    struct ListNode *nxt;
    bool result = deleteDupsOnce(&head, &nxt);
    
    while (result) {
        result = deleteDupsOnce(&head, &nxt);
    }

    return head;
}


int g_a[] = {1,1,1,2,3,3,3};

int main()
{
    struct ListNode *h = InitListNode(g_a, sizeof(g_a)/sizeof(int));
    h = deleteDuplicates(h);
    PrintListNode(h);
    FreeList(h);
}