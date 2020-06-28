#ifndef C_DATASTRUCTURES_BINARYTREE_H
#define C_DATASTRUCTURES_BINARYTREE_H
#include "Utils.h"

typedef struct BTreeNode{
    void **value;
    struct BTreeNode * right;
    struct BTreeNode * left;
}BTreeNode;


#endif //C_DATASTRUCTURES_BINARYTREE_H
