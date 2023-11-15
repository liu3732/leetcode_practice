#include <stdlib.h>
#include <assert.h>
#include <sys/queue.h>

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
    struct Node *next;
};

struct QEntry {
    struct Node *node;
    TAILQ_ENTRY(QEntry) entry;
};

TAILQ_HEAD(Queue, QEntry) g_queue = TAILQ_HEAD_INITIALIZER(g_queue);
int g_qlen = 0;

void PushHead(struct Node *node)
{
    struct QEntry *elem = (struct QEntry *)malloc(sizeof(struct QEntry));
    elem->node = node;

    g_qlen++;
    TAILQ_INSERT_HEAD(&g_queue, elem, entry);
    return;
}

struct Node *PopTail(void)
{
    if (g_qlen == 0) {
        return NULL;
    }

    struct QEntry *elem = TAILQ_LAST(&g_queue, Queue);
    TAILQ_REMOVE(&g_queue, elem, entry);
    struct Node* ret = elem->node;
    free(elem);
    g_qlen--;
    return ret;
}

void FreeQueue(void)
{
    struct QEntry *elem = NULL;
    struct QEntry *prev = NULL;
    TAILQ_FOREACH(elem, &g_queue, entry)
    {
        free(prev);
        prev = elem;
    }
    free(prev);
    return;
}

struct Node* connect(struct Node* root) {
    if(root == NULL) {
        return NULL;
    }
    PushHead(root);
    int len = g_qlen;
    while(!TAILQ_EMPTY(&g_queue)) {
        struct Node *prev = NULL;
        struct Node *cur = NULL;
        while(len > 0) {
            cur = PopTail();
            if (prev != NULL) {
                prev->next = cur;
            }
            if (cur->left) {
                PushHead(cur->left);
            }
            if (cur->right) {
                PushHead(cur->right);
            }
            prev = cur;
            len--;
        }
        len = g_qlen;
    }
    return root;
}

int main()
{
    return 0;
}