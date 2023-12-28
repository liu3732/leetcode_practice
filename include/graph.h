#ifndef __GRAPH__
#define __GRAPH__


struct Node {
    int val;
    int numNeighbors;
    struct Node** neighbors;
};

struct Node *createListGraph(int **input, int inputLen, int *colLens);
void freeListGraph(struct Node *node);

#endif