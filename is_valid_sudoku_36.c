#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int col_maps[9][9];
int row_maps[9][9];
int rec_maps[9][9];

char board[][9] = {
    {'5','3','.','.','7','.','.','.','.'},
    {'6','.','.','1','9','5','.','.','.'},
    {'.','9','8','.','.','.','.','6','.'},
    {'8','.','.','.','6','.','.','.','3'},
    {'4','.','.','8','.','3','.','.','1'},
    {'7','.','.','.','2','.','.','.','6'},
    {'.','6','.','.','.','.','2','8','.'},
    {'.','.','.','4','1','9','.','.','5'},
    {'.','.','.','.','8','.','.','7','9'}
};

char board02[][9] = 
{{'8','3','.','.','7','.','.','.','.'}
,{'6','.','.','1','9','5','.','.','.'}
,{'.','9','8','.','.','.','.','6','.'}
,{'8','.','.','.','6','.','.','.','3'}
,{'4','.','.','8','.','3','.','.','1'}
,{'7','.','.','.','2','.','.','.','6'}
,{'.','6','.','.','.','.','2','8','.'}
,{'.','.','.','4','1','9','.','.','5'}
,{'.','.','.','.','8','.','.','7','9'}};

int simple_ctoi(char c)
{
    if (c >= '1' && c <= '9')
    {
        return (int)(c - '0');
    }
    return -1;
}

bool isValidSudoku(char **board, int boardSize, int *boardColSize) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            col_maps[i][j] = 0;
            row_maps[i][j] = 0;
            rec_maps[i][j] = 0;
        }
    }
    for (int r = 0; r < boardSize; r++) {
        for (int c = 0; c < *boardColSize; c++) {
            int v = simple_ctoi(*(*(board+r)+c));
            if (v >= 1 && v <= 9) {
                if (col_maps[c][v-1] > 0 || row_maps[r][v-1] > 0 || rec_maps[r/3*3 + c/3][v-1] > 0) {
                    printf("no qualified in x(%d), y(%d).\n", r, c);
                    return false;
                }
                col_maps[c][v-1]++;
                row_maps[r][v-1]++;
                rec_maps[r/3*3 + c/3][v-1]++;
            }
        }
    }
    return true;
}


int main()
{
    int boardColSize = 9;
    
    char *p[9];

    for (int i = 0; i < 9; i++)
    {
        p[i] = &board[i][0];
    }
    assert(isValidSudoku((char **)p, 9, &boardColSize) == true);

    for (int i = 0; i < 9; i++)
    {
        p[i] = &board02[i][0];
    }
    assert(isValidSudoku((char **)p, 9, &boardColSize) == false);
    printf("test has been passed.\n");
}