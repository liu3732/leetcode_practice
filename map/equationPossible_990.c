#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define SMALL_CH_NUMS 26

typedef struct {
    char pa[SMALL_CH_NUMS];
    int cnt;
} uf_t;

void init(uf_t *uf)
{
    uf->cnt = 0;
    for (int i = 0; i < SMALL_CH_NUMS; i++) {
        uf->pa[i] = 0;
    }
}

bool is_exisited(uf_t *uf, char a)
{
    int i = a - 'a';
    if (uf->pa[i] != 0) {
        return true;
    }
    return false;
}

char find(uf_t *uf, char a)
{
    int ia = a - 'a';
    if (uf->pa[ia] != a) {
        uf->pa[ia] = find(uf, uf->pa[ia]);
    }

    return uf->pa[ia];
}

bool is_connect(uf_t *uf, char a, char b)
{
    int ia = a - 'a';
    int ib = b - 'a';
    
    uf->pa[ia] = find(uf, a);
    uf->pa[ib] = find(uf, b);

    if (uf->pa[ia] == uf->pa[ib]) {
        return true;
    } else {
        return false;
    }
}

void unify(uf_t *uf, char a, char b)
{
    int ia = a - 'a';
    int ib = b - 'a';
    
    uf->pa[ia] = find(uf, a);
    uf->pa[ib] = find(uf, b);

    if (uf->pa[ia] == uf->pa[ib]) {
        return;
    }

    int pia = uf->pa[ia] - 'a';
    uf->pa[pia] = uf->pa[ib];
    uf->cnt--;
}

void add(uf_t *uf, char a)
{
    int ia = a - 'a';
    uf->pa[ia] = a;
    uf->cnt++;
}

bool analysis(char *equation, char *outa, char *outb)
{
    int len = strlen(equation);
    assert(len == 4);

    *outa = equation[0];
    *outb = equation[3];
    if (equation[1] == '!' && equation[2] == '=') {
        return false;
    } else if (equation[1] == '=' && equation[2] == '=')
    {
        return true;
    } else {
        printf("unexpected input: %s\n", equation);
        exit(-1);
    }
}

bool equationsPossible(char** equations, int equationsSize) {
    uf_t *uf = (uf_t *)malloc(sizeof(uf_t));
    init(uf);
    bool ret = true;
    for (int i = 0; i < equationsSize; i++) {
        char a, b;
        bool is_equal;
        is_equal = analysis(equations[i], &a, &b);
        if (!is_exisited(uf, a)) {
            add(uf, a);
        }
        if (!is_exisited(uf, b)) {
            add(uf, b);
        }
        if(is_equal) {
            unify(uf, a, b);
        }
    }

    for (int i = 0; i < equationsSize; i++) {
        char a, b;
        bool is_equal;
        is_equal = analysis(equations[i], &a, &b);
        if (!is_equal && is_connect(uf, a, b)) {
            ret = false;
            break;
        }
    }    
    free(uf);
    return ret;
}

#define LEN 6
char *g_test[LEN] = {
    "f==a",
    "a==b",
    "f!=e",
    "a==c",
    "b==e",
    "c==f"
};

int main()
{
    char **test = (char **)malloc(sizeof(char *) * LEN);
    for (int r = 0; r < LEN; r++) {
        test[r] = g_test[r];
    }

    bool e = equationsPossible(test, LEN);
    printf("equality: %d\n", e);
    free(test);
}