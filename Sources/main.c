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

int main(int argc, char** argv)
{
	
    T_TREE* tree = createTree(NULL);
    
    destroyTree(tree, NULL);

    return 0;
}
