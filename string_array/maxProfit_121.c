#include <stdio.h>
#include <stdbool.h>

int maxProfit(int* prices, int pricesSize) {
    if (pricesSize < 2) {
        return 0;
    }

    int l = 0;
    int r = 1;

    int maxProfit = 0;
    // expand r to end 
    while(r < pricesSize) {
        if (prices[r] > prices[l]) {
            if (maxProfit < prices[r] - prices[l]) {
                maxProfit = prices[r] - prices[l];
            }
        }
        if (prices[r] < prices[l]) {
            l = r; // update l
        }
        r++;
    }
    return maxProfit;
}

int a[] = {7,6,4,3,1};

int main()
{
    printf("maxProfit: %d\n", maxProfit(a, sizeof(a)/sizeof(int)));    
}