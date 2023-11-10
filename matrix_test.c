#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define ROW 2
#define COL 2
int g_matrix[ROW][COL] = {
    {1, 2},
    {3, 4}
};

int main()
{
    int r = 1;
    int c = 1;

    int **p0 = g_matrix;
    // printf("p0[r][c] would oops: %d\n", p0[r][c]);
    
    int (*p1)[COL] = g_matrix;
    printf("p1[r][c] == g_matrix[r][c]: %d\n", p1[r][c]);

    int **p3 = (int **)malloc(ROW * sizeof(int *));
    for (int row = 0; row < ROW; row++) {
        p3[row] = (int *)malloc(COL * sizeof(int));
        for (int col = 0; col < COL; col++) {
            p3[row][col] = g_matrix[row][col];
        }
    }
    printf("p3[r][c] == g_matrix[r][c]: %d\n", p3[r][c]);

    int *p4 = g_matrix;
    printf("p4[r*COL + c] == g_matrix[r][c]: %d\n", p4[r*COL + c]);
}