#ifndef TREE_HUGGER_H_
#define TREE_HUGGER_H_

#include <stdbool.h>
#include "tree.h"
#include "stack.h"

typedef struct TreePos {
    float x;
    float y;
    float distl;
    float distr;
    bool exist;
} TreePos;

TreePos get_tree_pos(Node* tree, Stack* stack, float layer, float x_offset);

#endif // TREE_HUGGER_H_
