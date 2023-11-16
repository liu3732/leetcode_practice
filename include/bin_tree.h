#ifndef __TREE__
#define __TREE__

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

#define NULL_NODE __INT32_MAX__
#define null NULL_NODE

struct TreeNode *PreArrayToTree(int **p2a, unsigned int *p2num_size);
struct TreeNode *PostArrayToTree(int **p2a, unsigned int *p2num_size);
struct TreeNode *LayerArrayToTree(int *a, unsigned int num_size);
struct TreeNode* MallocTreeNode(int v);
void FreeTree(struct TreeNode *root);

#endif