#ifndef TREE_H
#define TREE_H

#define TREE_LEAVES_FROM_INTERNALS(N) ((N)+1)
#define TREE_NODES_FROM_INTERNALS(N) ((2*(N))+1)

#define TREE_INTERNALS_FROM_NODES(N) (((N)-1)/2)
#define TREE_LEAVES_FROM_NODES(N) (((N)+1)/2)

#define TREE_NODES_FROM_LEAVES(N) ((2*(N))-1)
#define TREE_INTERNALS_FROM_LEAVES(N) ((N)-1)

#include "common.h"

typedef struct TREEOPTIONS T_TREEOPTIONS;
typedef struct NODE T_NODE;
typedef struct TREE T_TREE;
typedef struct NODESTACK T_NODESTACK;

typedef void T_NODEDATA;
typedef T_NODEDATA*(*T_CREATENODEDATA_F)();
typedef void(*T_DESTROYNODEDATA_F)(T_NODEDATA*);

struct TREEOPTIONS {
    T_CREATENODEDATA_F createNodeData;
    T_DESTROYNODEDATA_F destroyNodeData;
};

struct NODE {
    int index;
    T_NODE* left;
    T_NODE* right;
    T_NODEDATA* data;
};

struct NODESTACK {
    unsigned int size;
    T_NODESTACK** stack;
    T_NODE* node;
};

struct TREE {
    T_NODE* root;
};

T_NODE* newNode();
T_NODE* createNode(unsigned int leafCount, int level);
void destroyNode(T_NODE* node);

T_NODESTACK* newNodeStack();

T_TREE* newTree();
T_TREE* createTree(unsigned int leafCount);
void destroyTree(T_TREE* tree);

extern T_TREEOPTIONS treeOptions;

//extern T_CREATENODEDATA_F defCreateNodeDataFunc;
//extern T_DESTROYNODEDATA_F defDestroyNodeDataFunc;





#endif /* TREE_H */