/*
 * @Author: liuxiaoxiang liu3732@gmail.com
 * @Date: 2023-11-02 23:04:10
 * @LastEditors: liu3732 liu3732@gmail.com
 * @LastEditTime: 2023-11-09 16:58:40
 * @FilePath: \leetcode_practice\solve_130.c
 * @Description: 
 * 
 * Copyright (c) 2023 by ${git_name_email}, All Rights Reserved. 
 */

#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

enum STATE {
    NO_CHECKED = 0,
    DONT_FLIP,
    TO_FLIP
};

enum STATE **g_state = NULL;

void set_flip_state_dfs(char** board, int boardSize, int* boardColSize, int row, int col)
{
    if (row >= boardSize || row < 0 || col >= *boardColSize || col < 0 ||  *(*(g_state + row) + col) != NO_CHECKED) {
        return;
    }
    if (board[row][col] == 'X') {
        return;
    }

    // now it's 'O'
    g_state[row][col] = DONT_FLIP;
    set_flip_state_dfs(board, boardSize, boardColSize, row+1, col);
    set_flip_state_dfs(board, boardSize, boardColSize, row-1, col);
    set_flip_state_dfs(board, boardSize, boardColSize, row, col+1);
    set_flip_state_dfs(board, boardSize, boardColSize, row, col-1);
    return;    
}

bool is_border(int m, int n, int boardSize, int *boardColSize)
{
    if (m == 0 || n == 0 || m == (boardSize - 1) || n == (*boardColSize - 1)) {
        return true;
    }
    return false;
}

void solve(char** board, int boardSize, int* boardColSize)
{
    // init state
    g_state = (enum STATE **)malloc(sizeof(enum STATE *) * boardSize);
    for (int m = 0; m < boardSize; m++) {
        *(g_state + m) = (enum STATE *)malloc(sizeof(enum STATE) * (*boardColSize));
        for (int n = 0; n < *boardColSize; n++) {
            *(*(g_state + m) + n) = NO_CHECKED;
        }
    }

    // check board state, change state from un_flip to to_flip.
    for (int m = 0; m < boardSize; m++) {
        for (int n = 0; n < *boardColSize; n++) {
            if (is_border(m, n, boardSize, boardColSize)) {
                set_flip_state_dfs(board, boardSize, boardColSize, m, n);
            }
        }
    }

    // do flip
    for (int m = 0; m < boardSize; m++) {
        for (int n = 0; n < *boardColSize; n++) {
            if (*(*(board + m) + n) == 'O' && *(*(g_state + m) + n) != DONT_FLIP) {
                *(*(board + m) + n) = 'X';
            }
        }
    }
    return;
}

#define ROW 1
#define COL 1
/*
char g_board[ROW][COL] = {
    {'X','X','X','X'},
    {'X','O','O','X'},
    {'X','X','O','X'},
    {'X','O','X','X'}
};
*/

char g_board[ROW][COL] = {
    {'X'}
};

int main()
{
    int row = ROW;
    int col = COL;
    char **input = malloc(sizeof(char *) * row);
    for (int m = 0; m < row; m++) {
        input[m] = malloc(sizeof(char) * col);
        for (int k = 0; k < col; k++) {
            input[m][k] = g_board[m][k];
        }
    }
    solve(input, row, &col);
    return 0;
}