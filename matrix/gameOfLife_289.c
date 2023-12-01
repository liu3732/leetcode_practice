#include <stdlib.h>
#include <stdio.h>

void setLifeNumsAround(int **lifeNums, int r, int c, int rowMax, int colMax)
{
    for (int m = r-1; m <= r+1; m++) {
        for (int n = c-1; n <= c+1; n++) {
            if (m == r && n == c) {
                continue;
            }
            if (m >= 0 && m < rowMax && n >= 0 && n < colMax) {
                lifeNums[m][n]++;
            }
        }
    }
}

void gameOfLife(int** board, int boardSize, int* boardColSize) {
    int **lifeNums = (int **)malloc(sizeof(int *) * boardSize);
    
    for (int r = 0; r < boardSize; r++) {
        lifeNums[r] = (int *)malloc(sizeof(int) * (*boardColSize));
        for (int c = 0; c < (*boardColSize); c++) {
            lifeNums[r][c] = 0;
        }
    }

    for (int r = 0; r < boardSize; r++) {
        for (int c = 0; c < (*boardColSize); c++) {
            if (board[r][c] == 1) {
                setLifeNumsAround(lifeNums, r, c, boardSize, *boardColSize);
            }
        }
    }

    for (int r = 0; r < boardSize; r++) {
        for (int c = 0; c < (*boardColSize); c++) {
            if(board[r][c] == 1) {
                if(lifeNums[r][c] < 2 || lifeNums[r][c] > 3) {
                    board[r][c] = 0;
                }
            } else {
                if(lifeNums[r][c] == 3) {
                    board[r][c] = 1;
                }
            }
        }
    }

    for (int r = 0; r < boardSize; r++) {
        free(lifeNums[r]);
    }
    free(lifeNums);
}

#define MAX_ROW 2
#define MAX_COL 2

int g_board[][MAX_COL] = {
    {1,1},
    {1,0}
};

int main()
{
    int **board = (int **)malloc(sizeof(int *) * MAX_ROW);
    for (int r = 0; r < MAX_ROW; r++) {
        board[r] = (int *)malloc(sizeof(int) *  MAX_COL);
        for (int c = 0; c < MAX_COL; c++) {
            board[r][c] = g_board[r][c];
        }
    }

    int maxColSize = MAX_COL;
    gameOfLife(board, MAX_ROW, &maxColSize);

    for (int r = 0; r < MAX_ROW; r++) {
        for(int c = 0; c < MAX_COL; c++) {
            printf("%d ", board[r][c]);
        }
        printf("\n");
    }
    for (int r = 0; r < MAX_ROW; r++) {
        free(board[r]);
    }
    free(board);
}