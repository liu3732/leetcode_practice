#include <queue.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

static int xy_to_idx(int x, int y, int n)
{
    int row_offset = (n-1) - x;

    int idx = row_offset*n;
    if (row_offset%2) {
        idx = idx + n - y;
    } else {
        idx = idx + y + 1;
    }
    return idx;
}

static void idx_to_xy(int *x, int *y, int n, int idx)
{
    int row_offset = (idx-1)/n;
    *x = (n-1) - row_offset;
    if (row_offset%2) {
        *y = (n-1) - (idx-1)%n;
    } else {
        *y = (idx-1)%n;
    }
    return;
}

void PushRelatedIdxs(struct queue *q_head, int idx, int **board, int n)
{
    for (int i = 1; i <= 6; i++) {
        int nxt_idx = idx+i;
        int x;
        int y;
        if (nxt_idx > n*n) {
            return;
        }
        idx_to_xy(&x, &y, n, nxt_idx);
        int nn_idx = board[x][y];
        if (nn_idx != -1) {
            nxt_idx = nn_idx;
        }

        int *elem = (QUEUE_TYPE)malloc(sizeof(int));
        *elem = nxt_idx;
        EnQueue(q_head, elem);
    }
}

#define MAX_NN 400
bool g_visited_map[MAX_NN+1];

int snakesAndLadders(int** board, int boardSize, int* boardColSize)
{
    int n = boardSize;
    int min_cnt = 0;

    struct queue *q_head = CreateQueue(n*n+1);
    int *elem_ptr = (int *)malloc(sizeof(int));
    *elem_ptr = 1;
    EnQueue(q_head, (QUEUE_TYPE)elem_ptr);

    while(!IsEmpty(q_head)) {
        int len = GetLen(q_head);
        memset((bool *)g_visited_map, false, sizeof(bool)*(MAX_NN+1));
        while(len > 0) {
            int *tmp_idx;
            PopQueue(q_head, (QUEUE_TYPE *)&tmp_idx);
            if (*tmp_idx == n*n) {
                goto free_buffers;
            }
            int idx = *tmp_idx;
            for (int i = 1; i <= 6; i++) {
                int nxt_idx = idx+i;
                int x;
                int y;
                if (nxt_idx > n*n) {
                    break;
                }
                idx_to_xy(&x, &y, n, nxt_idx);
                if (board[x][y] != -1) {
                    nxt_idx = board[x][y];
                }

                if (g_visited_map[nxt_idx]) {
                    continue;
                }
                int *elem = (QUEUE_TYPE)malloc(sizeof(int));
                *elem = nxt_idx;
                EnQueue(q_head, elem);
                g_visited_map[nxt_idx] = true;
            }
            free(tmp_idx);
            len--;
        }
        min_cnt++;
        if(min_cnt == n*n) {
            min_cnt = -1;
            goto free_buffers;
        }
    }
free_buffers:    
    while(!IsEmpty(q_head)) {
        int *tmp_idx;
        PopQueue(q_head, (QUEUE_TYPE *)&tmp_idx);
        free(tmp_idx);
    }
    FreeQueue(q_head);
    return min_cnt;
}

#if 0

#define NUM 6
int g_board[NUM][NUM] =
{
    {-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1},
    {-1,-1,-1,-1,-1,-1},
    {-1,35,-1,-1,13,-1},
    {-1,-1,-1,-1,-1,-1},
    {-1,15,-1,-1,-1,-1}
};
#endif


#define NUM 2
int g_board[NUM][NUM] =
{
    {-1, -1},
    {-1, 3}
};

#if 0
#define NUM 3
int g_board[NUM][NUM] = 
{
    {-1,4,-1},
    {6, 2, 6},
    {-1, 3, -1}
};
#endif

int test_id_3()
{
    int n = 3;
    int x = 0;
    int y = 0;

    int id = 1;
    idx_to_xy(&x, &y, n, id);
    assert(x == 2);
    assert(y == 0);
    assert(xy_to_idx(x, y, n) == id);

    id = 3;
    idx_to_xy(&x, &y, n, id);
    assert(x == 2);
    assert(y == 2);
    assert(xy_to_idx(x, y, n) == id);

    id = 4;
    idx_to_xy(&x, &y, n, id);
    assert(x == 1);
    assert(y == 2);
    assert(xy_to_idx(x, y, n) == id);

    id = 5;
    idx_to_xy(&x, &y, n, id);
    assert(x == 1);
    assert(y == 1);
    assert(xy_to_idx(x, y, n) == id);


    id = 7;
    idx_to_xy(&x, &y, n, id);
    assert(x == 0);
    assert(y == 0);
    assert(xy_to_idx(x, y, n) == id);

    id = 9;
    idx_to_xy(&x, &y, n, id);
    assert(x == 0);
    assert(y == 2);
    assert(xy_to_idx(x, y, n) == id);
}

int test_id_6()
{
    int x = 0;
    int y = 0;    
    int n = 6;

    idx_to_xy(&x, &y, n, 1);
    assert(x == 5);
    assert(y == 0);
    idx_to_xy(&x, &y, n, 2);
    assert(x == 5);
    assert(y == 1);
    idx_to_xy(&x, &y, n, 6);
    assert(x == 5);
    assert(y == 5);
    idx_to_xy(&x, &y, n, 7);
    assert(x == 4);
    assert(y == 5);    
    idx_to_xy(&x, &y, n, 31);
    assert(x == 0);
    assert(y == 5);    
    idx_to_xy(&x, &y, n, 36);
    assert(x == 0);
    assert(y == 0);

    int idx = 1;
    idx = xy_to_idx(0, 0, n);
    assert(idx == 36);

    idx = xy_to_idx(0, 5, n);
    assert(idx == 31);

    idx = xy_to_idx(1, 0, n);
    assert(idx == 25);

    idx = xy_to_idx(1, 5, n);
    assert(idx == 30);

    idx = xy_to_idx(5, 5, n);
    assert(idx == 6);
}

int main()
{

    if (NUM == 6) {
        test_id_6();
    } else if (NUM == 3) {
        test_id_3();
    }

    int **test_board = (int **)malloc(NUM*sizeof(int *));
    for (int i = 0; i < NUM; i++) {
        test_board[i] = (int *)malloc(NUM*sizeof(int));
        for (int j = 0; j < NUM; j++) {
            test_board[i][j] = g_board[i][j];
        }
    }

    int colSize = NUM;
    assert(snakesAndLadders(test_board, NUM, &colSize) == 1);
    printf("test has been passed\n");
}