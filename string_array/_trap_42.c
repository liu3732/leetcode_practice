#include <stdlib.h>
#include <stdio.h>

int min(int a, int b)
{
    return a > b ? b : a;
}

int trap(int* height, int heightSize) {
    if (heightSize < 3) {
        return 0;
    }

    int *left = (int *)malloc(sizeof(int) * heightSize);
    int *right = (int *)malloc(sizeof(int) * heightSize);

    int preHeight = 0;
    for (int i = 0; i < heightSize; i++) {
        if (height[i] >= preHeight) {
            left[i] = 0;
        } else {
            left[i] = preHeight - height[i];
        }
        preHeight = height[i];
    }

    preHeight = 0;
    for (int i = heightSize-1; i >= 0; i--) {
        if (height[i] >= preHeight) {
            right[i] = 0;
        } else {
            right[i] = preHeight - height[i];
        }
        preHeight = height[i];
    }

    int sum = 0;
    for (int i = 0; i < heightSize; i++) {
        sum += min(left[i], right[i]);
    }
    free(left);
    free(right);
    return sum;
}

int a[] = {0,1,0,2,1,0,1,3,2,1,2,1};
int main()
{
    printf("%d.\n", trap(a, sizeof(a)/sizeof(int)));
}