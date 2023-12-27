#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool **createMap(int m, int n)
{
    bool **ret = (bool **)malloc(sizeof(bool *) * m);
    for (int r = 0; r < m; r++) {
        ret[r] = (bool *)malloc(sizeof(bool) * n);
        memset(ret[r], false, sizeof(bool) * n);
    }
    return ret;
}

void freeMap(bool **map, int m)
{
    for (int r = 0; r < m; r++) {
        free(map[r]);
    }
    free(map);
}

void dfs_set_bit_map(bool **bit_map, int m, int n, char **grid, int r, int c)
{
    if (r >= m || c >= n || r < 0 || c < 0) {
        return;
    }
    if (bit_map[r][c] == true) {
        return;
    }
    if (grid[r][c] == '0') {
        return;
    }

    bit_map[r][c] = true;
    dfs_set_bit_map(bit_map, m, n, grid, r+1, c);
    dfs_set_bit_map(bit_map, m, n, grid, r-1, c);
    dfs_set_bit_map(bit_map, m, n, grid, r, c+1);
    dfs_set_bit_map(bit_map, m, n, grid, r, c-1);
    return;            
}

int numIslands(char** grid, int gridSize, int* gridColSize) {
    // create map
    bool **bit_map = createMap(gridSize, *gridColSize);

    int ret = 0;
    for (int m = 0; m < gridSize; m++) {
        for (int n = 0; n < *gridColSize; n++) {
            if(bit_map[m][n] == false && grid[m][n] == '1') {
                dfs_set_bit_map(bit_map, gridSize, *gridColSize, grid, m, n);
                ret++;
            }
        }
    }
    // clear map
    freeMap(bit_map, gridSize);

    return ret;
}

#define ROW 4
#define COL 5

char g_grid[][5] = {
  {'1','1','0','0','0'},
  {'1','1','0','0','0'},
  {'0','0','1','0','0'},
  {'0','0','0','1','1'}
};


int main()
{   
    int col = COL;
    char **g_ptr = (char **)malloc(sizeof(char *) * ROW);
    for (int r = 0; r < ROW; r++) {
        g_ptr[r] = (char *)malloc(sizeof(char) * COL);
        for (int c = 0; c < COL; c++) {
            g_ptr[r][c] = g_grid[r][c];
        }
    }

    int ret = numIslands(g_ptr, ROW, &col);
    printf("%d\n", ret);

    for (int r = 0; r < ROW; r++) {
        free(g_ptr[r]);
    }
    free(g_ptr);
}