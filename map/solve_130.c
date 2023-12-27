#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <uthash.h>
#include <string.h>

struct hash_entry {
    int k;
    UT_hash_handle hh;
};

bool **createVisited(int m, int n) {
    bool **ret = (bool **)malloc(sizeof(bool *) * m);
    for (int r = 0; r < m; r++) {
        ret[r] = (bool *)malloc(sizeof(bool) * n);
        memset(ret[r], false, sizeof(bool) * n);
    }
    return ret;
}

void freeVisited(bool **visited, int m)
{
    for (int r = 0; r < m; r++) {
        free(visited[r]);
    }
    free(visited);
}

void freeMap(struct hash_entry *hash_table)
{
    if (hash_table == NULL) {
        return;
    }
    struct hash_entry *el, *tmp;
    HASH_ITER(hh, hash_table, el, tmp)
    {
        HASH_DEL(hash_table, el);
        free(el);
    }
}

void dfs_set_map(bool **visited_map, char **board, int m, int n, int r, int c, struct hash_entry **h_map)
{
    if(r < 0 || r >= m || c < 0 || c >= n) {
        return;
    }
    if (board[r][c] == 'X' || visited_map[r][c] == true) {
        return;
    }

    visited_map[r][c] = true;
    int k = r * n + c;
    struct hash_entry *t = (struct hash_entry *)malloc(sizeof(struct hash_entry));
    t->k = k;
    HASH_ADD_INT(*h_map, k, t);
    
    dfs_set_map(visited_map, board, m, n, r+1, c, h_map);
    dfs_set_map(visited_map, board, m, n, r-1, c, h_map);
    dfs_set_map(visited_map, board, m, n, r, c+1, h_map);
    dfs_set_map(visited_map, board, m, n, r, c-1, h_map);
    return;    
}

void solve(char** board, int boardSize, int* boardColSize) {
    bool **visited_map = createVisited(boardSize, *boardColSize);
    struct hash_entry *map = NULL;

    int row_borders[] = {0, boardSize-1};
    int col_borders[] = {0, (*boardColSize)-1};
    for (int i = 0; i < 2; i++) {
        int r = row_borders[i];
        for (int c = 0; c < (*boardColSize); c++) {
            if (board[r][c] == 'O' && !visited_map[r][c]) {
                dfs_set_map(visited_map, board, boardSize, *boardColSize, r, c, &map);
            }
        }
    }

    for (int i = 0; i < 2; i++) {
        int c = col_borders[i];
        for (int r = 0; r < boardSize; r++) {
            if (board[r][c] == 'O' && !visited_map[r][c]) {
                dfs_set_map(visited_map, board, boardSize, *boardColSize, r, c, &map);
            }
        }
    }

    for(int r = 0; r < boardSize; r++) {
        for (int c = 0; c < *boardColSize; c++) {
            if (board[r][c] == 'O') {
                int k = r*(*boardColSize) + c;
                struct hash_entry *out;
                HASH_FIND_INT(map, &k, out);
                if (!out) {
                    board[r][c] = 'X';
                }
            }
        }
    }

    freeMap(map);
    freeVisited(visited_map, boardSize);
}

#define ROW 1
#define COL 1

char g_board[ROW][COL] = 
{   {'X'}
};

int main()
{
    char **board = (char **)malloc(sizeof(char *) * ROW);
    for (int r = 0; r < ROW; r++) {
        board[r] = (char *)malloc(sizeof(char) * COL);
        for (int c = 0; c < COL; c++) {
            board[r][c] = g_board[r][c];
        }
    }

    int col = COL;
    solve(board, ROW, &col);
    for (int r = 0; r < ROW; r++) {
        for (int c = 0; c < COL; c++) {
            printf("%c ", board[r][c]);
        }
        printf("\n");
        free(board[r]);
    }
    free(board);
}