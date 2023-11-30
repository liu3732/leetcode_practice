#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define RIGHT 0
#define DOWN 1
#define LEFT 2
#define UP 3
#define DMAX 4


/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* spiralOrder(int** matrix, int matrixSize, int* matrixColSize, int* returnSize) {


    *returnSize = matrixSize * (*matrixColSize);

    int *ret = (int *)malloc((*returnSize) * sizeof(int));
    if (matrixSize == 1) {
        for (int c = 0; c < *matrixColSize; c++) {
            ret[c] = matrix[0][c];
        }
        return ret;
    } else if (*matrixColSize == 1)
    {
        for (int r = 0; r < matrixSize; r++) {
            ret[r] = matrix[r][0];
        }
        return ret;
    }
    

    bool *visted_row = (bool *)malloc(matrixSize * sizeof(bool));
    memset(visted_row, 0, matrixSize * sizeof(bool));
    bool *visted_col = (bool *)malloc(*matrixColSize * sizeof(bool));
    memset(visted_col, 0, *matrixColSize * sizeof(bool));

    int i = 0, j = 0;
    int direction = RIGHT;
    for (int k = 0; k < *returnSize; ) {
        if (i < matrixSize &&  j < *matrixColSize) {
            ret[k++] = matrix[i][j];
        }
        
        switch(direction) {
            case RIGHT:
                j++;
                if (j >= *matrixColSize - 1 || visted_col[j+1]) {
                    if(i < matrixSize) {
                        visted_row[i] = true;
                    }
                    direction = DOWN;
                }
                break;
            case DOWN:
                i++;
                if (i >= matrixSize - 1 || visted_row[i+1]) {
                    if (j < *matrixColSize) {
                        visted_col[j] = true;
                    }
                    direction = LEFT;
                }
                break;
            case LEFT:
                j--;
                if (j <= 0 || visted_col[j-1]) {
                    if (i < matrixSize) {
                        visted_row[i] = true;
                    }
                    direction = UP;
                }
                break;
            case UP:
                i--;
                if (i <= 0 || visted_row[i-1]) {
                    if (j < *matrixColSize) {
                        visted_col[j] = true;
                    }
                    direction = RIGHT;
                }
                break;
        }
    }

    free(visted_row);
    free(visted_col);
    return ret;
}

#define MAX_ROW_SIZE 3
#define MAX_COL_SIZE 1
int g_test[MAX_ROW_SIZE][MAX_COL_SIZE] = {
    {7},
    {9},
    {6}
};

int main()
{
    int **test = (int **)malloc(sizeof(int *) * MAX_ROW_SIZE);
    for (int r = 0; r < MAX_ROW_SIZE; r++) {
        test[r] = (int *)malloc(sizeof(int) * MAX_COL_SIZE);
        for (int c = 0; c < MAX_COL_SIZE; c++) {
            test[r][c] = g_test[r][c];
        }
    }
    int max_col_size = MAX_COL_SIZE;
    int retSize = 0;

    int *ret = spiralOrder(test, MAX_ROW_SIZE, &max_col_size, &retSize);
    for (int i = 0; i < retSize; i++) {
        printf("%d ", ret[i]);
    }
    printf("\n");

    free(ret);

    for (int r = 0; r < MAX_ROW_SIZE; r++) {
        free(test[r]);
    }
    free(test);
}