#include <stdio.h>
#include <sys/queue.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct elem {
    char *ch;
    TAILQ_ENTRY(elem) entries;
};
typedef struct elem elem_t;

TAILQ_HEAD(queue, elem);
typedef struct queue queue_t;

void push(queue_t *q, char *ch)
{
    elem_t *new_elem = (elem_t *)malloc(sizeof(elem_t));
    new_elem->ch = ch;
    TAILQ_INSERT_TAIL(q, new_elem, entries);
}

bool pop(queue_t *q, char **out)
{
    if (TAILQ_EMPTY(q)) {
        return false;
    }
    elem_t *p = TAILQ_LAST(q, queue);
    *out = p->ch;
    TAILQ_REMOVE(q, p, entries);
    return true;
}

char *top(queue_t *q)
{
    elem_t *p = TAILQ_LAST(q, queue);
    if (p == NULL) {
        return NULL;
    }
    return p->ch;
}

queue_t *create(void)
{
    queue_t *ret = (queue_t *)malloc(sizeof(queue_t));
    TAILQ_INIT(ret);
    return ret;
}

void free_q(queue_t *q)
{
    while (!TAILQ_EMPTY(q)) {
        elem_t *elem = TAILQ_LAST(q, queue);
        TAILQ_REMOVE(q, elem, entries);
        free(elem->ch);
        free(elem);
    }
    free(q);
}

int ilen(int v)
{
    
    int ret = 1;
    if (v < 0) {
        v = -v;
        ret++;
    }
    v = v/10;
    while (v > 0) {
        ret++;
        v = v/10;
    }
    return ret;
}

char *str_op(char *a, char *b)
{
    int ca = atoi(a);
    int cb = atoi(b);
    int ret = ca + cb;

    int retLen = ilen(ret);
    char *result = (char *)malloc(retLen + 1);
    sprintf(result, "%d", ret);
    return result;
}

bool cal_queue(queue_t *q, char **ret)
{
    char *a = NULL;
    if (!pop(q, &a)) {
        return false;
    }

    char *b;
    while (!TAILQ_EMPTY(q)) {
        if (!pop(q, &b)) {
            return false;
        }
        char *result = str_op(a, b);
        free(a);
        free(b);
        a = result;
    }
    *ret = a;
    return true;
}

char *get_token(char *s, int *len)
{
    char *token = NULL;
    if (s[0] == '(' || s[0] == ')' || s[0] == '+' || 
        (s[0] == '-' && s[1] == '(')) {
        token = (char *)malloc(2);
        token[0] = s[0];
        token[1] = '\0';
        *len = 1;
    } else if (s[0] == ' ') {
        *len = 0;
        return NULL;
    } else {
        char *end;
        int v = strtol(s, &end, 10); 
        if (end == s) {
            *len = 0;
            return NULL;
        }
        *len = end - s;
        token = (char *)malloc((*len) + 1);
        strncpy(token, s, (*len));
        token[(*len)] = '\0';
    }
    return token;
}

char *remove_blank(const char *s)
{
    int ori_len = strlen(s) + 1;
    int dst_len = 0;
    char *ret = NULL;
    for (int i = 0; i < ori_len; i++) {
        if(s[i] == ' ') {
            continue;
        }
        dst_len++;
    }

    ret = (char *)malloc(dst_len);
    int j = 0;
    for (int i = 0; i < ori_len; i++) {
        if(s[i] == ' ') {
            continue;
        }
        ret[j++] = s[i];
    }

    return ret;
}

int calculate(char* s) {
    s = remove_blank(s);
    int len = strlen(s);

    queue_t *q_sym = create();
    queue_t *q_cal = create();

    for (int i = 0; i < len;) {
        int token_len = 0;
        char *token = get_token(&s[i], &token_len);
        if (token_len == 0) {
            i++;
            continue;
        }
        switch(*token) {
            case ')':
                char *in;
                if (!pop(q_sym, &in)) {
                    return -1;
                }
                while(*in != '(') {
                    push(q_cal, in);
                    if(!pop(q_sym, &in)) {
                        return -1;
                    }
                }
                free(token);
                free(in);
                char *result = NULL;
                if (!cal_queue(q_cal, &result)) {
                    return -1;
                }
                char *tmp = top(q_sym);
                if (tmp != NULL && tmp[0] == '-' && strlen(tmp) == 1) {
                    pop(q_sym, &tmp);
                    if (result[0] == '-') {
                        free(tmp);
                        int num_len = strlen(result)-1+1;
                        tmp = malloc(num_len);
                        strncpy(tmp, &result[1], num_len);
                    } else {
                        int num_len = strlen(result)+1;
                        tmp = realloc(tmp, num_len+1);
                        strncpy(&tmp[1], result, num_len);
                    }
                    push(q_sym, tmp);
                    free(result);
                } else {
                    push(q_sym, result);
                }
                i++;
                break;
            case ' ':
            case '+':
                free(token);
                i++;
                break;
            default:
                push(q_sym, token);
                i += token_len;
                break;
        }
    }

    while(!TAILQ_EMPTY(q_sym)) {
        char *tmp;
        pop(q_sym, &tmp);
        push(q_cal, tmp);
    }
    char *result;
    cal_queue(q_cal, &result);

    int ret = 0;
    char *end;
    ret = strtol(result, &end, 10);
    if (*end != '\0' || end == result) {
        return -1;
    }
    free_q(q_cal);
    free_q(q_sym);
    free(result);
    free(s);
    return ret;
}


int main()
{
    char *s = "- (3 + (4 + 5))";
    int ret = calculate(s);
    printf("%d\n", ret);
}