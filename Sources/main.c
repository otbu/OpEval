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

T_NODEDATA* createData() {
    return NULL;
}
void destroyData(T_NODEDATA* data) {
    free(data);
}

/*
# magic python 3 code:
def all_possible_trees_2(n):
    if n == 1:
        return 'L'
    list_nodes = list()
    for split in range(1, n):
        gen_left = all_possible_trees_2(split)
        gen_right = all_possible_trees_2(n - split)
        for l in gen_left:
            for r in gen_right:
                list_nodes.append([l,r])
    return list_nodes

    Observations:

    You need a stack ADT that supports push and can contain other stack
    objects. Similar to lists in python, although pop is not necessary but
    can probably added easily. Also, the stack must have a size as well.

    This stack must be iterable, so we can loop over all all possible sub-tree,
    and push each of ...

    Does the stack need to support nodes?
    Do we need a list of treenodes?

*/

T_NODESTACK* all_possible_trees(unsigned int n)
{
    if (n == 1) {
        T_NODESTACK* stack = newNodeStack();
        stack->node = newNode();
        return stack;
    }
    for (unsigned int split = 1; split < n; n++) {
        T_NODESTACK* leftStack = all_possible_trees(split);
        T_NODESTACK* rightStack = all_possible_trees(n-split);
    }

}




int main(int argc, char** argv)
{
    treeOptions.createNodeData = createData;
    treeOptions.destroyNodeData = destroyData;

    unsigned int leafCount = 4;
    T_TREE* tree = createTree(leafCount);
    
    destroyTree(tree);

    return 0;
}
