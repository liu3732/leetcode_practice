#include <stdio.h>
#include <assert.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int dfsProfit(int *prices, int pricesSize, int gainedProfit)
{
    assert(gainedProfit >= 0);

    if(pricesSize < 2) {
        return gainedProfit;
    }
    int sell = 1;
    int buy = 0;
    if(pricesSize == 2) {
        int profit = max(prices[sell] - prices[buy], 0);
        return profit > 0 ? gainedProfit + profit : gainedProfit;
    }

    int retMax = 0;
    while (sell < pricesSize) {
        int tmpProfit = max(prices[sell] - prices[buy], 0);
        int tmpMax = dfsProfit(&prices[sell], pricesSize - sell, gainedProfit+tmpProfit);
        retMax = max(tmpMax, retMax);

        // next forward
        if (prices[sell] < prices[buy]) {
            buy = sell;
        }
        sell++;
    }
    return retMax;
}

int maxProfit_dfs(int* prices, int pricesSize) {
    return dfsProfit(prices, pricesSize, 0);
}

int maxProfit(int* prices, int pricesSize) {
    int ret = 0;

    if (pricesSize  < 2) {
        return ret;
    }

    int buy = 0;
    int sell = 1;

    while (sell < pricesSize) {
        if (prices[sell] < prices[buy]) {
            buy = sell;
            sell++;
            continue;
        }
        ret += (prices[sell] - prices[buy]);
        buy = sell;
        sell++;
    }
    return ret;
}

int a[] = {1,2,3,4,5};
int main()
{
    printf("maxprofit: %d\n", maxProfit(a, sizeof(a)/sizeof(int)));
}