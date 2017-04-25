#include <stdlib.h>
#include <stdio.h>

/*
    What are we attempting to do here:

    - Iterate through binary trees in a deterministic order, but otherwise undefined.
    - These binary trees have up to 9 leaves, although there is a special-case with 10 leaves.
    - Also, they have 8-9 internal nodes.
    - Tree traversal is post-order.

*/

#include "tree.h"

#define TEST_NLEAF 4
#define TEST_NTREE 5
#define TEST_NNODE 7

T_NODEDATA* createData() {
    return NULL;
}
void destroyData(T_NODEDATA* data) {
    free(data);
}

void analyzeNode(T_NODE* node, int* index, unsigned char* arr)
{
    if (node->left != NULL) {
        analyzeNode(node->left, index, arr);
    }
    if (node->right != NULL) {
        analyzeNode(node->right, index, arr);
    }

    if ((node->left == NULL) && (node->right == NULL)) {
        arr[(*index)++] = '1';
    }
    else {
        arr[(*index)++] = '0';
    }
}

int main(int argc, char** argv)
{
    
    T_NODE** nodeCache = NULL;
    T_NODE** trees = createAllTrees_v2(NULL, TEST_NLEAF, 0);
    //unsigned int size = TEST_NTREE;
    T_NODE nodes[TEST_NTREE];
    unsigned char arrs[TEST_NTREE][TEST_NNODE + 1];

    int index = 0;
    for (unsigned int i = 0; i < TEST_NTREE; i++) {
        nodes[i] = *(trees[i]); // copy?
        index = 0;
        arrs[i][TEST_NNODE] = '\0';
        analyzeNode(&(nodes[i]), &index, arrs[i]);
    }

    for (unsigned int i = TEST_NTREE-1; i >= 0; i--) {
        destroyNode(trees[i]);
    }
    /*
    T_NODEARRAY* trees = createAllTrees(TEST_NLEAF);
    
    T_NODE nodes[TEST_NTREE];
    unsigned char arrs[TEST_NTREE][TEST_NNODE+1];

    int index = 0;
    for (unsigned int i = 0; i < trees->size; i++) {
        nodes[i] = *(trees->array[i]->node); // copy?
        index = 0;
        arrs[i][TEST_NNODE] = '\0';
        analyzeNode(&(nodes[i]), &index, arrs[i]);
    }
    
    destroyNodeArray(trees);
    */

    return 0;
}
