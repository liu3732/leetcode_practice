#ifndef __LIST__
struct ListNode {
    int val;
    struct ListNode *next;
};

struct ListNode *InitListNode(int *array, int arraySize);
void PrintListNode(struct ListNode *listHead);
struct ListNode *GetXthNode(struct ListNode *listNode, int xth);
void InsertListTail(struct ListNode **listHead, struct ListNode *new);
void FreeList(struct ListNode *listHead);

#endif