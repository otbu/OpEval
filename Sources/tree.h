#ifndef TREE_H
#define TREE_H

#include "common.h"

typedef void T_EXTRANODEDATA;
typedef struct NODEDATA T_NODEDATA;
typedef struct NODE T_NODE;
typedef struct TREE T_TREE;
typedef T_EXTRANODEDATA*(*T_CREATE_EXTRANODEDATA_F)(T_NODEDATA*);
typedef void(*T_DESTROY_EXTRANODEDATA_F)(T_EXTRANODEDATA*);

struct NODEDATA {
    int index;
    unsigned int children;
};

struct NODE {
    T_NODEDATA* data;
    T_EXTRANODEDATA* extraData;
    T_NODE* left;
    T_NODE* right;
};

struct TREE {
    T_NODE* root;
};

T_NODEDATA* newNodeData();
T_NODEDATA* createNodeData();
void destroyNodeData(T_NODEDATA* data);

T_NODE* newNode();
T_NODE* createNode(T_CREATE_EXTRANODEDATA_F createExtraNode);
void destroyNode(T_NODE* node, T_DESTROY_EXTRANODEDATA_F destroyExtraNode);

T_TREE* newTree();
T_TREE* createTree(T_CREATE_EXTRANODEDATA_F createExtraNode);
void destroyTree(T_TREE* tree, T_DESTROY_EXTRANODEDATA_F destroyExtraNode);

extern T_CREATE_EXTRANODEDATA_F defaultCreateExtraNodeData;
extern T_DESTROY_EXTRANODEDATA_F defaultDestroyExtraNodeData;





#endif /* TREE_H */