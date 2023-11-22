#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *roman;
    int  v;
} romanType;

const romanType romanMap[] = {
    {
        .roman = "MMM",
        .v = 3000
    },
    {
        .roman = "MM",
        .v = 2000
    },
    {
        .roman = "M",
        .v = 1000
    },
    {
        .roman = "CM",
        .v = 900
    },
    {
        .roman = "DCCC",
        .v = 800
    },
    {
        .roman = "DCC",
        .v = 700
    },
    {
        .roman = "DC",
        .v = 600
    },
    {
        .roman = "D",
        .v = 500
    },
    {
        .roman = "CD",
        .v = 400
    },
    {
        .roman = "CCC",
        .v = 300
    },
    {
        .roman = "CC",
        .v = 200
    },
    {
        .roman = "C",
        .v = 100
    },
    {
        .roman = "XC",
        .v = 90
    },
    {
        .roman = "LXXX",
        .v = 80
    },
    {
        .roman = "LXX",
        .v = 70
    },
    {
        .roman = "LX",
        .v = 60
    },
    {
        .roman = "L",
        .v = 50
    },
    {
        .roman = "XL",
        .v = 40
    },
    {
        .roman = "XXX",
        .v = 30
    },
    {
        .roman = "XX",
        .v = 20
    },
    {
        .roman = "X",
        .v = 10
    },
    {
        .roman = "IX",
        .v = 9
    },
    {
        .roman = "VIII",
        .v = 8
    },
    {
        .roman = "VII",
        .v = 7
    },
    {
        .roman = "VI",
        .v = 6
    },
    {
        .roman = "V",
        .v = 5
    },
    {
        .roman = "IV",
        .v = 4
    },
    {
        .roman = "III",
        .v = 3
    },
    {
        .roman = "II",
        .v = 2
    },
    {
        .roman = "I",
        .v = 1
    }
};

typedef struct {
    char *a[30];
    int head;
    int tail;
} queue_t;

void enQueue(queue_t *s, char *ele)
{
    s->a[s->tail++] = ele;
    return;
}

queue_t *create()
{
    queue_t *ptr = (queue_t *)malloc(sizeof(queue_t));
    ptr->head = 0;
    ptr->tail = 0;
    return ptr;
}

char *popQueue(queue_t *s)
{
    return s->a[s->head++];
}

bool isEmpty(queue_t *s)
{
    return s->head == s->tail;
}

char* intToRoman(int num) {
    int gi = 0;
    int totalLen = sizeof(romanMap)/sizeof(romanType);
    char *ret = NULL;
    int retLen = 0;
    queue_t *s = create();

    for (int gi = 0; gi < totalLen; gi++) {
        if (num == 0) {
            break;
        }
        if(num - romanMap[gi].v >= 0) {
            enQueue(s, romanMap[gi].roman);
            retLen += strlen(romanMap[gi].roman);
            num -= romanMap[gi].v;
        }
    }

    assert(num == 0);
    ret = (char *)malloc(retLen+1);
    int i = 0;
    while(!isEmpty(s)) {
        char *tmp = popQueue(s);
        strncpy(&ret[i], tmp, strlen(tmp));
        i += strlen(tmp);
    }
    free(s);
    ret[i] = '\0';
    return ret;
}

int main()
{
    int v = 1994;
    char *ret = intToRoman(v);
    printf("roman:%s", ret);
    free(ret);
}