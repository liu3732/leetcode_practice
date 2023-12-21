#include <sys/queue.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define MAX_LEN 100

typedef struct min_heap {
    int *values;
    int len;
    int max_len;
} min_heap_t;

struct entry {
    int val;
    int idx;
    TAILQ_ENTRY(entry) entries;
};

TAILQ_HEAD(queue_t, entry);


int get_parent(int idx)
{
    if (idx == 1) {
        return 1;
    }
    return idx/2;
}

int left_child(int idx)
{
    return 2*idx;
}

int right_child(int idx)
{
    return 2*idx + 1;
}

void swap(min_heap_t *h, int a, int b)
{
    int tmp = h->values[a];
    h->values[a] = h->values[b];
    h->values[b] = tmp;
}

int insert(min_heap_t *h, int elem)
{
    if (h->len == h->max_len) {
        h->max_len = 2*h->max_len;
        h->values = (int *)realloc(h->values, (h->max_len+1) * sizeof(int));
    }
    h->len++;
    h->values[h->len] = elem;

    int i = h->len;
    int p_i = get_parent(i);
    int ret = i;
    while (h->values[i] < h->values[p_i]) {
        // swap
        swap(h, i, p_i);
        ret = p_i;
        // update;
        i = p_i;
        p_i = get_parent(i);
    }
    return ret;
}



void delete(min_heap_t *h, int root)
{
    h->values[root] = __INT32_MAX__;


    while (root < h->len) {
        int l = 2*root;
        int r = l+1;
        if (l == h->len) {
            swap(h, l, root);
            break;
        } else if (l > h->len) {
            break;
        } else {
            int c;
            if(h->values[l] < h->values[r]) {
                c = l;
            } else {
                c = r;
            }
            swap(h, c, root);
            root = c;
        }
    }
    h->len--;
    return;
}

typedef struct {
    struct queue_t q_head;
    min_heap_t heap;
} MinStack;


MinStack* minStackCreate() {
    MinStack *ret = (MinStack *)malloc(sizeof(MinStack));
    ret->heap.len = 0;
    ret->heap.max_len = MAX_LEN;
    ret->heap.values = (int *)malloc(sizeof(int) * (MAX_LEN + 1));
    TAILQ_INIT(&ret->q_head);
    return ret;
}

void minStackPush(MinStack* obj, int val) {
    int idx = insert(&obj->heap, val);
    
    struct entry *elem = (struct entry *)malloc(sizeof(struct entry));
    elem->val = val;
    elem->idx = idx;
    TAILQ_INSERT_TAIL(&obj->q_head, elem, entries);
}

void minStackPop(MinStack* obj) {
    assert(obj->heap.len > 0);

    struct entry *elem = TAILQ_LAST(&obj->q_head, queue_t);
    
    delete(&obj->heap, elem->idx);
    TAILQ_REMOVE(&obj->q_head, elem, entries);
    free(elem);
}

int minStackTop(MinStack* obj) {
    struct entry *elem = TAILQ_LAST(&obj->q_head, queue_t);
    return elem->val;
}

int minStackGetMin(MinStack* obj) {
    return obj->heap.values[1];
}

void minStackFree(MinStack* obj) {
    while(!TAILQ_EMPTY(&obj->q_head)) {
        struct entry *elem = TAILQ_LAST(&obj->q_head, queue_t);
        TAILQ_REMOVE(&obj->q_head, elem, entries);
        free(elem);
    }
    free(obj->heap.values);
    free(obj);
}

/**
 * Your MinStack struct will be instantiated and called as such:
 * MinStack* obj = minStackCreate();
 * minStackPush(obj, val);
 
 * minStackPop(obj);
 
 * int param_3 = minStackTop(obj);
 
 * int param_4 = minStackGetMin(obj);
 
 * minStackFree(obj);
*/

int main()
{
    MinStack *obj = minStackCreate();
    minStackPush(obj, -2);
    minStackPush(obj, 0);
    minStackPush(obj, -3);

    assert(minStackTop(obj) == -3);
    assert(minStackGetMin(obj) == -3);
    minStackPop(obj);
    assert(minStackTop(obj) == 0);
    assert(minStackGetMin(obj) == -2);

    minStackFree(obj);
}