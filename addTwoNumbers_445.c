#include "list.h"
#include "assert.h"
#include "stdint.h"
#include "stdlib.h"

#define MAX_LEN 100
struct Stack {
    struct ListNode *s[MAX_LEN];
    uint32_t top;
};

struct Stack g_s1 = {
    .top = 0
};

struct Stack g_s2 = {
    .top = 0
};

void pushElem(struct Stack *stack, struct ListNode *p)
{
    assert(stack->top < MAX_LEN);
    stack->s[stack->top++] = p;
}

struct ListNode *popElem(struct Stack *stack)
{
    if (stack->top == 0) {
        return NULL;
    }
    struct ListNode *ret = stack->s[stack->top-1];
    stack->top--;
    return ret;
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {

    // init stack
    g_s1.top = 0;
    g_s2.top = 0;

    // push l1 to s1
    struct ListNode *p = l1;
    while(p != NULL) {
        pushElem(&g_s1, p);
        p = p->next;
    }

    // push l2 to s2
    p = l2;
    while(p != NULL) {
        pushElem(&g_s2, p);
        p = p->next;
    }

    int carry = 0;
    struct ListNode *ret = NULL;
    while (1) {
        // pop s1 -> v1, pop s2 -> v2
        // v1 + v2 ->  p
        // p -> next = ret
        // ret = p
        struct ListNode *v1 = popElem(&g_s1);
        struct ListNode *v2 = popElem(&g_s2); 
        if (v1 != NULL && v2 != NULL) {
            struct ListNode *new = (struct ListNode *)malloc(sizeof(struct ListNode));
            new->val = (v1->val + v2->val + carry)%10;
            carry = (v1->val + v2->val + carry)/10;
            new->next = ret;
            ret = new;
        } else if (v1 == NULL && v2 != NULL) {
            struct ListNode *new = (struct ListNode *)malloc(sizeof(struct ListNode));
            new->val = (v2->val + carry)%10;
            carry = (v2->val + carry)/10;
            new->next = ret;
            ret = new;
        } else if (v1 != NULL && v2 == NULL) {
            struct ListNode *new = (struct ListNode *)malloc(sizeof(struct ListNode));
            new->val = (v1->val + carry)%10;
            carry = (v1->val + carry)/10;
            new->next = ret;
            ret = new;
        } else {
            if (carry > 0) {
                struct ListNode *new = (struct ListNode *)malloc(sizeof(struct ListNode));
                new->val = carry;
                new->next = ret;
                ret = new;
            }
            break;
        }
    }

    return ret;
}

int a[] = {4,4,3};
int b[] = {7,5,6,4};

int main()
{
    struct ListNode *l1 = InitListNode(a, sizeof(a)/sizeof(int));
    struct ListNode *l2 = InitListNode(b, sizeof(b)/sizeof(int));

    struct ListNode *sum = addTwoNumbers(l1, l2);

    PrintListNode(sum);
    return 0;
}