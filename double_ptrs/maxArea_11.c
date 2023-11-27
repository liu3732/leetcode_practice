#include <stdio.h>
#include <stdbool.h>

int min_idx(int *height, int l, int r)
{
    return height[l] < height[r] ? l : r;
}

int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

int maxArea(int* height, int heightSize) {
    int l = 0;
    int r = heightSize - 1;
    int maxArea = 0;

    while(l < r) {
        if (height[l] > height[r]) {
            maxArea = max(maxArea, height[r] * (r-l));
            r--;
        } else {
            maxArea = max(maxArea, height[l] * (r-l));
            l++;
        }
    }

    return maxArea;
}

int g_height[] = {1,8,6,2,5,4,8,3,7};

int main()
{
    printf("%d.\n", maxArea(g_height, sizeof(g_height)/sizeof(int)));
}