#include "tree.h"

// set these to to NULL as we cannot define default handlers:
T_CREATE_EXTRANODEDATA_F defaultCreateExtraNodeData = NULL;
T_DESTROY_EXTRANODEDATA_F defaultDestroyExtraNodeData = NULL;

T_NODEDATA* newNodeData() {

    T_NODEDATA* nodeData = malloc(sizeof(T_NODEDATA));
    if (nodeData != NULL) {
        nodeData->index = 0;
        nodeData->children = 0;
    }
    return nodeData;
}

T_NODEDATA* createNodeData() { 
    return newNodeData();
}

void destroyNodeData(T_NODEDATA* nodeData) {

    if (nodeData != NULL)
        free(nodeData);
}

T_NODE* newNode()
{
    T_NODE* node = malloc(sizeof(T_NODE));
    if (node != NULL)
    {
        node->data = NULL;
        node->extraData = NULL;
        node->left = NULL;
        node->right = NULL;
    }
    return node;
}

T_NODE* createNode(T_CREATE_EXTRANODEDATA_F createExtraNode) {

    T_NODE* node = newNode();
    
    if (node != NULL) {
        node->left = createNode(createExtraNode);
        node->right = createNode(createExtraNode);
        node->data = createNodeData();

        if (createExtraNode == NULL)
            createExtraNode = defaultCreateExtraNodeData;

        if (createExtraNode != NULL)
            node->extraData = (*createExtraNode)(node->data);
    }
    return node;

}
void destroyNode(T_NODE* node, T_DESTROY_EXTRANODEDATA_F destroyExtraNode) {

    if (node != NULL) {
        destroyNodeData(node->data);
        node->data = NULL;
        destroyNode(node->left, destroyExtraNode);
        node->left = NULL;
        destroyNode(node->right, destroyExtraNode);
        node->right = NULL;

        if (destroyExtraNode == NULL)
            destroyExtraNode = defaultDestroyExtraNodeData;

        if (destroyExtraNode != NULL) {
            (*destroyExtraNode)(node->extraData);
            node->extraData = NULL;
        }

        free(node);
    }
}

T_TREE* newTree()
{
    T_TREE* tree = malloc(sizeof(T_TREE));
    if (tree != NULL) {
        tree->root = NULL;
    }
    return tree;
}

T_TREE* createTree(T_CREATE_EXTRANODEDATA_F createExtraNode) {

    T_TREE* tree = newTree();
    if (tree != NULL) {
        tree->root = createNode(createExtraNode);
    }
    return tree;
}

void destroyTree(T_TREE* tree, T_DESTROY_EXTRANODEDATA_F destroyExtraNode) {

    if (tree != NULL) {
        destroyNode(tree->root, destroyExtraNode);
        tree->root = NULL;
        free(tree);
    }
}