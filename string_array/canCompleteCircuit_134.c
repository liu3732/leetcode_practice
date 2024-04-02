#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int canCompleteCircuit(int* gas, int gasSize, int* cost, int costSize) {
    assert(gasSize == costSize);
    int *dif = (int *)malloc(gasSize * sizeof(int));
    for (int i = 0; i < gasSize; i++) {
        dif[i] = gas[i] - cost[i];
    }

    int retval = -1;
    for (int l = 0; l < gasSize; ) {
        if (dif[l] >= 0) {
            int r = (l+1)%gasSize;
            int sum = dif[l];
            while(sum >= 0) {
                if (l == r) {
                    retval = l;
                    goto out;
                }
                sum += dif[r];
                r = (r+1)%gasSize;
            }
            if (r <= l) {
                goto out;
            } else {
                l = r;
            }
        } else {
            l++;
        }
    }

out:
    free(dif);
    return retval;
}

int gas[] = {2,3,4};
int cost[] = {3,4,3};

int main()
{
    int len = sizeof(gas)/sizeof(int);
    printf("idx: %d\n",canCompleteCircuit(gas, len, cost, len));
}