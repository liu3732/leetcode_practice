#include <stdlib.h>
#include <sys/queue.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

struct elem {
    long val;
    TAILQ_ENTRY(elem) elems;
};

TAILQ_HEAD(queue, elem);

typedef struct queue queue_t;

void push(queue_t *q, long token)
{
    struct elem *p = (struct elem *)malloc(sizeof(struct elem));
    p->val = token;
    TAILQ_INSERT_TAIL(q, p, elems);
    return;
}

bool pop(queue_t *q, long *ret)
{
    if(TAILQ_EMPTY(q)) {
        return false;
    }
    struct elem *p = TAILQ_LAST(q, queue);
    *ret = p->val;
    TAILQ_REMOVE(q, p, elems);
    free(p);
    return true;
}

queue_t *create(void)
{
    queue_t *ret = (queue_t *)malloc(sizeof(queue_t));
    TAILQ_INIT(ret);
    return ret;
}

void free_q(queue_t *q)
{
    while(!TAILQ_EMPTY(q))
    {
        struct elem *p = TAILQ_LAST(q, queue);
        TAILQ_REMOVE(q, p, elems);
        free(p);
    }
    free(q);
}

enum {
    ADD,
    DEC,
    MUL,
    DIV,
    INV
};

int getCaclType(char *token)
{
    int len = strlen(token);
    if (strncmp(token, "+", len) == 0) {
        return ADD;
    } else if (strncmp(token, "-", len) == 0)
    {
        return DEC;
    } else if (strncmp(token, "*", len) == 0)
    {
        return MUL;
    } else if (strncmp(token, "/", len) == 0)
    {
        return DIV;
    }
    return INV;
}

bool getNum(char *token, long *number)
{
    char *end;
    *number = strtol(token, &end, 10); 
    if (end == token || *end != '\0' || errno == ERANGE) {
        return false;
    }
    return true;
}

int evalRPN(char** tokens, int tokensSize) {
    queue_t *q_head = create();
    
    for (int i = 0; i < tokensSize; i++) {
        long number;
        if (getNum(tokens[i], &number)) {
            push(q_head, number);
        } else {
            int operation = getCaclType(tokens[i]);
            long b = 0;
            long a = 0;
            if (!pop(q_head, &b)) {
                return -1;
            }
            if (!pop(q_head, &a)) {
                return -1;
            }
            switch(operation) {
                case ADD:        
                    push(q_head, a+b);
                    break;
                case DEC:
                    push(q_head, a-b);
                    break;
                case MUL:
                    push(q_head, a*b);
                    break;
                case DIV:
                    push(q_head, a/b);
                    break;
                default:
                    printf("No legal law.\n");
                    return -1;
                    break;
            }
        }       
    }
    long ret;
    if (!pop(q_head, &ret)) {
        return -1;
    }
    free_q(q_head);
    return ret;
}

#define NELEM 13
char *g_tokens[NELEM] = {
    "10","6","9","3","+","-11","*","/","*","17","+","5","+"
};

int main()
{
    char **tokens = (char **)malloc(sizeof(g_tokens));
    for (int i = 0; i < NELEM; i++) {
        tokens[i] = (char *)malloc(sizeof(g_tokens[i]));
        strncpy(tokens[i], g_tokens[i], sizeof(g_tokens[i]));
    }

    int ret = evalRPN(tokens, NELEM);
    printf("%d\n", ret);

    for (int i = 0; i < NELEM; i++) {
        free(tokens[i]);
    }
    free(tokens);
}