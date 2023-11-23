#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char a[1000];
    int head;
    int tail;
} queue_t;

queue_t *create(void) {
    queue_t *ret = (queue_t *)malloc(sizeof(queue_t));
    ret->tail = 0;
    ret->head = 0;
    return ret;
}

void push(queue_t *q, char input) {
    q->a[q->tail++] = input;
}

char pop(queue_t *q) {
    return q->a[q->head++];
}

bool isEmpty(queue_t *q) {
    return q->tail == q->head;
}

char* convert(char* s, int numRows) {
    if (numRows == 1) {
        return s;
    }

    queue_t **queues = (queue_t **)malloc(numRows * sizeof(queue_t *));
    for (int r = 0; r < numRows; r++) {
        queues[r] = create();
    }

    int back_sz = numRows - 2;
    int *rotate_r = (int *)malloc((numRows + back_sz)*sizeof(int));
    for (int i = 0; i < numRows + back_sz; i++) {
        if (i < numRows) {
            rotate_r[i] = i;
        } else {
            rotate_r[i] = numRows- 1 - (i - numRows + 1);
        }
        printf("%d ", rotate_r[i]);
    }
    printf("\n");

    int len = strlen(s);
    int r_i = 0;
    for (int i = 0; i < len; i++) {
        int r = rotate_r[r_i];
        push(queues[r], s[i]);
        r_i = (r_i + 1) % (numRows + back_sz);
    }

    int i = 0;
    char *ret = (char *)malloc(len + 1);
    for (int r = 0; r < numRows; r++) {
        while(!isEmpty(queues[r])) {
            ret[i++] = pop(queues[r]);
        }
        free(queues[r]);
    }
    free(queues);
    ret[i] = '\0';
    free(rotate_r);
    return ret;
}

int main()
{
    char *s = "PAYPALISHIRING";
    int numRows = 1;
    printf("%s.\n", convert(s, numRows));
}