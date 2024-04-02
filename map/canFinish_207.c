#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_COURSES 2000

typedef struct node node_t;
struct node {
    node_t *next;
    int val;
};

typedef struct {
    node_t **nodes;
    int len;
} map_t;

void freeNodeList(node_t *listHead)
{
    if (!listHead) {
        return;
    }
    node_t *next = listHead->next;
    while(next != NULL) {
        free(listHead);

        listHead = next;
        next = listHead->next;
    }
    free(listHead);
}

bool isInList(node_t *listHead, int v)
{
    while(listHead != NULL) {
        if(listHead->val == v) {
            return true;
        }
        listHead = listHead->next;
    }
    return false;
}

void addHead(node_t **listHead, int v)
{
    if(isInList(*listHead, v)) {
        return;
    }

    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->val = v;

    new_node->next = *listHead;
    *listHead = new_node;
}

map_t *createMap(int max)
{
    map_t *ret = (map_t *)malloc(sizeof(map_t));
    ret->nodes = (node_t **)malloc(sizeof(node_t *) * max);
    ret->len = max;
    for (int i = 0; i < max; i++) {
        ret->nodes[i] = NULL;
    }
    return ret;
}

void freeMap(map_t *m)
{
    for (int i = 0; i < m->len; i++) {
        if(m->nodes[i]) {
            freeNodeList(m->nodes[i]);
        }
    }
    free(m->nodes);
    free(m);
}

bool canFinish(int numCourses, int** prerequisites, int prerequisitesSize, int* prerequisitesColSize) {
    map_t *preMap = createMap(numCourses);

    for (int i = 0; i < prerequisitesSize; i++) {
        int source = prerequisites[i][0];
        int target = prerequisites[i][1];
        if(!preMap->nodes[source]) {
            addHead(&preMap->nodes[source], source);
        }
        addHead(&preMap->nodes[source]->next, target);
    }

    for (int i = 0; i < numCourses; i++) {
        if(preMap->nodes[i]) {
            node_t *ptr = preMap->nodes[i]->next;
            int v = i;
            while(ptr != NULL) {
                if(isInList(preMap->nodes[ptr->val], v)) {
                    freeMap(preMap);
                    return false;
                }
                ptr = ptr->next;
            }
        }
    }
    freeMap(preMap);
    return true;
}

int g_pres[][2] = {
    {1, 0},
    {0, 1}
};

int main()
{
    int numCourses = 2;
    int preNums = 2;
    int *colSize = (int *)malloc(sizeof(int) * preNums);
    int **pres = (int **)malloc(sizeof(int *) * preNums);

    for (int i = 0; i < preNums; i++) {
        pres[i] = g_pres[i];
        colSize[i] = 2;
    }

    bool ret = canFinish(numCourses, pres, preNums, colSize);
    printf("%d\n", ret);

    free(colSize);
    free(pres);
}