#include <list.h>
#include <stdlib.h>

struct ListNode *min_and_forward(struct ListNode **list1, struct ListNode **list2)
{
    if (*list1 == NULL && *list2 == NULL) {
        return NULL;
    }
    struct ListNode *ret = NULL;
    if (*list2 == NULL) {
        ret = *list1;
        (*list1) = (*list1)->next;
        return ret;
    }
    if (*list1 == NULL) {
        ret = *list2;       
        (*list2) = (*list2)->next;
        return ret;
    }

    if ((*list1)->val < (*list2)->val) {
        ret = *list1;
        (*list1) = (*list1)->next;
        return ret;
    } else {
        ret = *list2;       
        (*list2) = (*list2)->next;
        return ret;
    }
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode *ret = NULL;

    if (list1 == NULL) {
        return list2;
    }

    if (list2 == NULL) {
        return list1;
    }

    ret = min_and_forward(&list1, &list2);
    struct ListNode *ptr = ret;

    while (ptr != NULL) {
        ptr->next = min_and_forward(&list1, &list2);
        ptr = ptr->next;
    }

    return ret;
}


int g_a[] = {1,2,4};
int g_b[] = {1,3,4};

int main()
{
    struct ListNode *a = InitListNode(g_a, sizeof(g_a)/sizeof(int));
    struct ListNode *b = InitListNode(g_b, sizeof(g_b)/sizeof(int));

    struct ListNode *c = mergeTwoLists(NULL, NULL);
    PrintListNode(c);
    
    FreeList(c);
}