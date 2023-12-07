#include <stdbool.h>
#include <uthash.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int n;
    UT_hash_handle hh;    
} map_t;

int caculate(int n)
{
    int sum = 0;
    while (n > 0) {
        sum += (n%10)*(n%10);
        n = n/10;
    }
    return sum;
}

bool is_in_map(map_t *m, int n)
{
    map_t *cur;
    HASH_FIND_INT(m, &n, cur);
    if(cur != NULL) {
        return true;
    } else {
        return false;
    }
}


void free_map(map_t *m)
{
    map_t *cur, *tmp;
    HASH_ITER(hh, m, cur, tmp)
    {
        HASH_DEL(m, cur);
        free(cur);
    }
}

void add_map(map_t **m, int n)
{
    map_t *cur = (map_t *)malloc(sizeof(map_t));
    cur->n = n;
    HASH_ADD_INT(*m, n, cur);
}

bool isHappy(int n) {
    map_t *m = NULL;

    while(1) {
        if (is_in_map(m, n)) {
            return false;
        }
        int next_n = caculate(n);
        if(next_n == 1) {
            return true;
        }

        add_map(&m, n);
        n = next_n;
    }    
}


int main()
{
    int m = 2;
    printf("isHappy(%d) = %d.\n", m, isHappy(m));
}
