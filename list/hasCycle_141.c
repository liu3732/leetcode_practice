#include "list.h"
#include "stdbool.h"
#include "uthash.h"
#include "assert.h"
#include "stdio.h"

struct list_node_hash {
    struct ListNode *key;
    UT_hash_handle hh;
};

struct list_node_hash *g_list_nodes = NULL;

void add_list_node(struct list_node_hash **s)
{
    HASH_ADD_PTR(g_list_nodes, key, *s);
}

struct list_node_hash *find_list_node(struct ListNode *key)
{
    struct list_node_hash *ret_list_node_hash = NULL;
    HASH_FIND_PTR(g_list_nodes, &key, ret_list_node_hash);
    return ret_list_node_hash;
}

void delete_list_nodes() {
    struct list_node_hash *current_list_node, *tmp;

    HASH_ITER(hh, g_list_nodes, current_list_node, tmp) {
        HASH_DEL(g_list_nodes, current_list_node); 
        free(current_list_node);
    }
}

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
bool hasCycle(struct ListNode *head)
{
    struct ListNode *l_p = head;
    struct list_node_hash *h_p = NULL;
    bool ret_val = false;

    while (l_p != NULL) {
        h_p = find_list_node(l_p);
        if (h_p != NULL) {
            ret_val = true;
            break;
        }

        h_p = (struct list_node_hash *)malloc(sizeof(struct list_node_hash));
        h_p->key = l_p;
        add_list_node(&h_p);
        l_p = l_p->next;
    }
    delete_list_nodes();
    return ret_val;
}


int test_array[] = {1};

int main()
{
    struct ListNode* listHead = InitListNode(test_array, sizeof(test_array)/sizeof(int));
    //struct ListNode* first = GetXthNode(listHead, 1);
    //struct ListNode* zero = GetXthNode(listHead, 0);
    //first->next = zero;

    assert(hasCycle(listHead) == false);
    printf("Test has been passed");
}