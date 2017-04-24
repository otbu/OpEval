#include "tree.h"

// =============================================================================
T_TREEOPTIONS treeOptions = { 
    // set these to to NULL as we cannot define default handlers:
    NULL, // createNodeData
    NULL  // destroyNodeData
};

const unsigned long int catalanNumbers[20] = {
    1,1,2,5,14,42,132,429,1430,4862,16796,58786,
    208012,742900,2674440,9694845,35357670,129644790,
    477638700, 1767263190
};
// -----------------------------------------------------------------------------

// =============================================================================
T_NODE* newNode() {
    T_NODE* node = malloc(sizeof(T_NODE));
    if (node != NULL)
    {
        node->index = 0;
        node->left = NULL;
        node->right = NULL;
        node->data = NULL;
    }
    printf("newNode(%p)\n", (void*)node);
    return node;
}
// -----------------------------------------------------------------------------

// =============================================================================
T_NODEARRAY* newNodeArray(unsigned int size) {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    T_NODEARRAY* nodeArray = malloc(sizeof(T_NODEARRAY));
    if (nodeArray != NULL)
    {
        nodeArray->size = size;
        nodeArray->array = NULL;
        nodeArray->node = NULL;

        if (size != 0) {
            nodeArray->array = malloc(size * sizeof(T_NODEARRAY*));
            if (nodeArray->array != NULL) {
                for (unsigned int n = 0; n < size; n++) {
                    nodeArray->array[n] = newNodeArray(0);
                }
            }
        }
        else if (size == 0)
        {
            nodeArray->node = newNode();
        }
    }
    return nodeArray;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}
// -----------------------------------------------------------------------------

// =============================================================================
void destroyNodeArray(T_NODEARRAY* nodeArray) {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    if (nodeArray != NULL)
    {
        if (nodeArray->node != NULL) {
            destroyNode(nodeArray->node);
            nodeArray->node = NULL;
        }
        
        if (nodeArray->array != NULL) {
            for (unsigned int n = 0; n < nodeArray->size; n++) {
                destroyNodeArray(nodeArray->array[n]);
                nodeArray->array[n] = NULL;
            }
            free(nodeArray->array);
            nodeArray->array = NULL;
        }

        nodeArray->size = 0;
        free(nodeArray);
    }
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}
// -----------------------------------------------------------------------------

/*
def all_possible_trees_2b(n) :

    list_nodes = [Node()] * list_catalan[(n - 1)]
    num_rotIdx = 0
    for split in range(1, n) :
        list_left = all_possible_trees_2b(split)
        list_right = all_possible_trees_2b(n - split)

        num_leftLen = len(list_left)#; print(num_leftLen)
        num_rightLen = len(list_right)#; print(num_rightLen)

        for num_leftIdx in range(num_leftLen) :
            for num_rightIdx in range(num_rightLen) :
                list_currRotLeft = list_left[num_leftIdx]
                list_currRotRight = list_right[num_rightIdx]
                list_nodes[num_rotIdx] = Node(list_currRotLeft, list_currRotRight)
                num_rotIdx += 1
    return list_nodes
*/

// =============================================================================
T_NODEARRAY* createAllTrees(unsigned int n) {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    T_NODEARRAY* arr = NULL;
    if (n > 0) {
        arr = newNodeArray(catalanNumbers[n - 1]);
    }
    if (n > 1) {
        unsigned int num_rotIdx = 0;
        for (unsigned int s = 1; s < n; s++) {
            T_NODEARRAY* arrL = createAllTrees(s);
            T_NODEARRAY* arrR = createAllTrees(n - s);

            for (unsigned int kL = 0; kL < arrL->size; kL++) {
                T_NODEARRAY* arrL_curr = arrL->array[kL];
                for (unsigned int kR = 0; kR < arrR->size; kR++) {
                    T_NODEARRAY* arrR_curr = arrR->array[kR];
                    
                    //if (arrL->size == 1)
                    //    arrL_curr->node->index = 1; // mark as leaf
                    //if (arrR->size == 1)
                    //    arrR_curr->node->index = 1; // mark as leaf
                    arr->array[num_rotIdx]->node->left = newNode();
                    *(arr->array[num_rotIdx]->node->left) = *(arrL_curr->node);
                    //arrL_curr->node = NULL; // copied, nullify pointer

                    arr->array[num_rotIdx]->node->right = newNode();
                    *(arr->array[num_rotIdx]->node->right) = *(arrR_curr->node);
                    //arrR_curr->node = NULL; // copied, nullify pointer

                    num_rotIdx++;
                }
            }
            //destroyNodeArray(arrL);
            //arrL == NULL;
            //destroyNodeArray(arrR);
            //arrR == NULL;
        }
    }
    return arr;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}
// -----------------------------------------------------------------------------

// =============================================================================
T_NODE* createNode(unsigned int leafCount, int level) {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    T_NODE* node = newNode();
    if (node != NULL)
    {
        node->left = createNode(leafCount, level + 1);
        node->right = createNode(leafCount, level + 1);
        if (treeOptions.createNodeData != NULL)
            node->data = (*treeOptions.createNodeData)(node->data);
    }
    
    return node;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}
// -----------------------------------------------------------------------------

// =============================================================================
void destroyNode(T_NODE* node) {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    printf("destroyNode(%p)\n", (void*)node);
    
    if (node != NULL) {
        destroyNode(node->left);
        node->left = NULL;
        destroyNode(node->right);
        node->right = NULL;

        if (treeOptions.destroyNodeData != NULL) {
            (*treeOptions.destroyNodeData)(node->data);
            node->data = NULL;
        }

        free(node);
    }
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}
// -----------------------------------------------------------------------------

// =============================================================================
T_TREE* newTree() {
    T_TREE* tree = malloc(sizeof(T_TREE));
    if (tree != NULL) {
        tree->root = NULL;
    }
    return tree;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}
// -----------------------------------------------------------------------------

// =============================================================================
T_TREE* createTree(unsigned int leafCount) {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    T_TREE* tree = newTree();
    if (tree != NULL) {
        //tree->root = createNode();
    }
    return tree;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}
// -----------------------------------------------------------------------------

// =============================================================================
void destroyTree(T_TREE* tree) {
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    if (tree != NULL) {
        destroyNode(tree->root);
        tree->root = NULL;
        free(tree);
    }
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
}
// -----------------------------------------------------------------------------