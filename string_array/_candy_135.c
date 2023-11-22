#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#define MAX_STACK_LEN 20000
typedef struct {
    int a[MAX_STACK_LEN];
    int top;
    int prev;
} StackType;

StackType *createStack(void) {
    StackType *ptr = (StackType *)malloc(sizeof(StackType));
    ptr->top = 0;
    ptr->prev = -1;
    return ptr;
}

void freeStack(StackType *ptr) {
    free(ptr);
    return;
}

bool isStackEmpty(StackType *ptr) {
    return ptr->top == 0;
}

void pushStack(StackType *ptr, int v) {
    ptr->a[ptr->top++] = v;
    return;
}

int popStack(StackType *ptr) {
    return ptr->a[--ptr->top];
}

int getTop(StackType *ptr) {
    return ptr->a[ptr->top-1];
}

int popAllStackAndSum(StackType *s) {
    int sum = 0;
    
    
    int curCandy = 1;
    if (s->a[0] == s->a[s->top-1]) {
        curCandy = 2;
    } else {
        curCandy = 1;
    }

    sum += curCandy;
    int prevRating = popStack(s);

    while(!isStackEmpty(s)) {
        int curRating = popStack(s);
        assert(curRating >= prevRating);
        if(curRating > prevRating) {
            curCandy++;
        }
        sum += curCandy;
        prevRating = curRating;
    }
    return sum;
}

int candy(int* ratings, int ratingsSize) {
    if (ratingsSize == 1) {
        return 1;
    }

    StackType *s = createStack();
    
    int sum = 0;

    for (int i = 0; i < ratingsSize; i++) {
        if(isStackEmpty(s)) {
            pushStack(s, ratings[i]);
        } else {
            int top = getTop(s);
            if(ratings[i] <= top) {
                pushStack(s, ratings[i]);
            } else // ratings[i] > top
            {
                sum += popAllStackAndSum(s);
                s->prev = i-1;
                pushStack(s, ratings[i]);
            }
        }
    }
    if (!isStackEmpty(s)) {
        sum += popAllStackAndSum(s);
    }
    return sum;
}

int ratings[] = {1, 2, 2};
int main()
{
    int size = sizeof(ratings)/sizeof(int);
    printf("candy sum: %d\n", candy(ratings, size));
}