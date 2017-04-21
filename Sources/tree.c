#include "tree.h"


T_TREEOPTIONS treeOptions = { 
    // set these to to NULL as we cannot define default handlers:
    NULL, // createNodeData
    NULL  // destroyNodeData
};

T_NODE* newNode()
{
    T_NODE* node = malloc(sizeof(T_NODE));
    if (node != NULL)
    {
        node->index = 0;
        node->left = NULL;
        node->right = NULL;
        node->data = NULL;
    }
    return node;
}

T_NODE* createNode(unsigned int leafCount, int level) {

    T_NODE* node = newNode();
    
    if (node != NULL) {

        if (node->index <= TREE_NODES_FROM_LEAVES(leafCount))
        {
            node->left = createNode(leafCount, level + 1);
            node->right = createNode(leafCount, level + 1);
        }

        if (treeOptions.createNodeData != NULL)
            node->data = (*treeOptions.createNodeData)(node->data);
    }
    return node;

}

void destroyNode(T_NODE* node) {

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
}

T_NODESTACK* newNodeStack() {
    T_NODESTACK* stack = malloc(sizeof(T_NODESTACK));
    if (stack != NULL) {
        stack->size = 0;
        stack->stack = NULL;
        stack->node = NULL;
    }
    return stack;
}

T_TREE* newTree()
{
    T_TREE* tree = malloc(sizeof(T_TREE));
    if (tree != NULL) {
        tree->root = NULL;
    }
    return tree;
}

T_TREE* createTree(unsigned int leafCount) {

    T_TREE* tree = newTree();
    if (tree != NULL) {
        tree->root = createNode();
    }
    return tree;
}

void destroyTree(T_TREE* tree) {

    if (tree != NULL) {
        destroyNode(tree->root);
        tree->root = NULL;
        free(tree);
    }
}