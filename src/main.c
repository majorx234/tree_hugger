#include <stdio.h>
#include <stdbool.h>
#include "tree.h"
#include "stack.h"
#include "tree_hugger.h"

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
    float max_radius = 0.0f;
    TreeMap* tree_map = calc_tree_poses(tree, 0, &max_radius);
    print_hash_map(tree_map);

    return 0;
}
