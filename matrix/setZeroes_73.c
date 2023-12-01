#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void set_flag_around(bool **flag, int r, int c, int rowLen, int colLen)
{
    for (int m = 0; m < rowLen; m++) {
        flag[m][c] = true;
    }

    for (int n = 0; n < colLen; n++) {
        flag[r][n] = true;
    }
}

void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    bool **need_set = (bool **)malloc(sizeof(bool *) * matrixSize);
    for (int r = 0; r < matrixSize; r++) {
        need_set[r] = (bool *)malloc(sizeof(bool) * (*matrixColSize));
        for (int c = 0; c < *matrixColSize; c++) {
            need_set[r][c] = false;
        }
    }

    for (int r = 0; r < matrixSize; r++) {
        for (int c = 0; c < *matrixColSize; c++) {
            if(matrix[r][c] == 0) {
                set_flag_around(need_set, r, c, matrixSize, *matrixColSize);
            }
        }
    }

    for (int r = 0; r < matrixSize; r++) {
        for (int c = 0; c < *matrixColSize; c++) {
            if(need_set[r][c] == true) {
                matrix[r][c] = 0;
            }
        }
    }

    for (int r = 0; r < matrixSize; r++) {
        free(need_set[r]);
    }
    free(need_set);
}

#define MAX_ROW 3
#define MAX_COL 4

int g_m[][MAX_COL] = {
    {0,1,2,0},
    {3,4,5,2},
    {1,3,1,5}
};

int main()
{
    int max_col = MAX_COL;

    int **input = (int **)malloc(sizeof(int *) * MAX_ROW);
    for (int r = 0; r < MAX_ROW; r++) {
        input[r] = (int *)malloc(sizeof(int) * MAX_COL);
        for (int c = 0; c < MAX_COL; c++) {
            input[r][c] = g_m[r][c];
        }
    }
    setZeroes(input, MAX_ROW, &max_col);

    for (int r = 0; r < MAX_ROW; r++) {
        for (int c = 0; c < MAX_COL; c++) {
            printf("%d ", input[r][c]);
        }
        printf("\n");
    }

    for (int r = 0; r < MAX_ROW; r++) {
        free(input[r]);
    }
    free(input);
}