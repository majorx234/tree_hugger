#include <stdio.h>
#include <stdbool.h>
#include "tree.h"
#include "stack.h"
#include "tree_hugger.h"

void visualize_tree(Node* tree, float layer) {
    Stack* stack = create_stack();
    TreePos tree_pos = get_tree_pos(tree, stack, layer, 0.0);
    // stack is ready with all points
    // lets print it!
    stack_print(stack);
}

int main(void)
{
    int root_data = 10;
    Node *tree = create_node(root_data);

    /*
    tree_insert(&tree, 2);
    tree_insert(&tree, 11);
    */

    tree_insert(&tree, 2);
    tree_insert(&tree, 5);
    tree_insert(&tree, 17);
    tree_insert(&tree, 1);
    tree_insert(&tree, 4);
    tree_insert(&tree, 3);

    // 10, 2, 1, 5, 17
    tree_print_preorder(tree);
    printf("---------------------\n");
    visualize_tree(tree, 0);

    return 0;
}
