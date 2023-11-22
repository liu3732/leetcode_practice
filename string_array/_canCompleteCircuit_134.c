#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    assert(gasSize == costSize);
    int *left = (int *)malloc(sizeof(int) * gasSize);

    for (int i = 0; i < gasSize; i++) {
        left[i] = gas[i] - cost[i];
    }

    int ret = 0;
    int *accumulate = (int *)malloc(sizeof(int) * gasSize);
    
    while (ret < gasSize) {
        int i = 0;
        for (; i < gasSize; i++) {
            int idx = (ret + i)%gasSize;
            if (i == 0) {
                accumulate[i] = left[idx];
            } else {
                accumulate[i] = accumulate[i-1]+left[idx];
            }
            if (accumulate[i] < 0) {
                break;
            }
        }
        if (i == gasSize) {
            break;
        }
        ret++;
    }
    free(accumulate);
    free(left);
    if (ret == gasSize) {
        return -1;
    }
    return ret;
}

int gas[] = {1,2,3,4,5};
int cost[] = {3,4,5,1,2};

int main()
{
    int len = sizeof(gas)/sizeof(int);
    printf("idx: %d\n",canCompleteCircuit(gas, len, cost, len));
}