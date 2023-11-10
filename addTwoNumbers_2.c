#include "list.h"
#include "assert.h"
#include "stdint.h"
#include "stdlib.h"

struct ListNode *getNextElem(struct ListNode *node)
{
    if (node == NULL) {
        return NULL;
    }
    return node->next;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int carry = 0;
    struct ListNode *head = NULL;

    while (1) {
        // v1 + v2 ->  p
        // insert p to tail of head 
        if (l1 != NULL && l2 != NULL) {
            struct ListNode *new = (struct ListNode *)malloc(sizeof(struct ListNode));
            new->val = (l1->val + l2->val + carry)%10;
            carry = (l1->val + l2->val + carry)/10;
            InsertListTail(&head, new);
        } else if (l1 == NULL && l2 != NULL) {
            struct ListNode *new = (struct ListNode *)malloc(sizeof(struct ListNode));
            new->val = (l2->val + carry)%10;
            carry = (l2->val + carry)/10;
            InsertListTail(&head, new);
        } else if (l1 != NULL && l2 == NULL) {
            struct ListNode *new = (struct ListNode *)malloc(sizeof(struct ListNode));
            new->val = (l1->val + carry)%10;
            carry = (l1->val + carry)/10;
            InsertListTail(&head, new);
        } else {
            if (carry > 0) {
                struct ListNode *new = (struct ListNode *)malloc(sizeof(struct ListNode));
                new->val = carry;
                InsertListTail(&head, new);
            }
            break;
        }
        
        // update l1 & l2
        l1 = getNextElem(l1);
        l2 = getNextElem(l2);
    }

    return head;
}

int a[] = {2,4,3};
int b[] = {5,6,4};

int main()
{
    struct ListNode *l1 = InitListNode(a, sizeof(a)/sizeof(int));
    struct ListNode *l2 = InitListNode(b, sizeof(b)/sizeof(int));

    struct ListNode *sum = addTwoNumbers(l1, l2);

    PrintListNode(sum);
    return 0;
}