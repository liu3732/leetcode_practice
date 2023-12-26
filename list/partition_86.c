#include <list.h>
#include <stdlib.h>

void partitionBy(struct ListNode **left, struct ListNode **right, struct ListNode *head, int x)
{
    struct ListNode *left_ptr = NULL;
    struct ListNode *right_ptr = NULL;

    while (head != NULL) {
        if (head->val < x) {
            if (*left == NULL) {
                *left = head;
                left_ptr = *left;
            } else {
                left_ptr->next = head;
                left_ptr = left_ptr->next;
            }
        } else {
            if (*right == NULL) {
                *right = head;
                right_ptr = *right;
            } else {
                right_ptr->next = head;
                right_ptr = right_ptr->next;
            }
        }
        head = head->next;
    }
    if (left_ptr) {
        left_ptr->next = *right;
    }
    if (right_ptr) {
        right_ptr->next = NULL;
    }
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* partition(struct ListNode* head, int x) {
    struct ListNode *left = NULL;
    struct ListNode *right = NULL;
    partitionBy(&left, &right, head, x);
    if (left == NULL) {
        return right;
    } else {
        return left;
    }
}

int g_a[] = {2, 1};
int main()
{
    struct ListNode *h = InitListNode(g_a, sizeof(g_a)/sizeof(int));
    h = partition(h, 2);
    PrintListNode(h);
    FreeList(h);
}