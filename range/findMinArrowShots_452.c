#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b)
{
    int *ca = *(int **)a;
    int *cb = *(int **)b;
    return ca[0] > cb[0] ? 1 : -1;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int findMinArrowShots(int** points, int pointsSize, int* pointsColSize){
    if (pointsSize < 2) {
        return 1;
    }

    qsort(points, pointsSize, sizeof(int *), compare);

    int ans = 1;
    int i = 0;
    int l = points[i][0];
    int r = points[i][1];
    
    for (i = 1; i < pointsSize; i++) {
        if (points[i][0] <= r) {
            r = min(points[i][1], r);
        } else {
            ans++;
            l = points[i][0];
            r = points[i][1];
        }
    }
    return ans;
}

#define NELEM 4
int points[][NELEM] = 
{
    {1, 2},
    {2, 3},
    {3, 4},
    {4, 5}
};

int main()
{
    int colSize = 2;
    int **p = (int **)malloc(sizeof(int *) * NELEM);
    for (int r = 0; r < NELEM; r++) {
        p[r] = (int *)malloc(sizeof(int) * 2);
        p[r][0] = points[r][0];
        p[r][1] = points[r][1];
    }
    printf("result: %d\n", findMinArrowShots(p, NELEM, &colSize));
    for (int r = 0; r < NELEM; r++) {
        free(p[r]);
    }
    free(p);
}