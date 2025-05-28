#include "tree_hugger.h"
#include "tree.h"
#include "stack.h"
#include <stdbool.h>

TreePos get_tree_pos(Node* tree, Stack* stack, float layer, float x_offset){
  TreePos tree_pos = {
    .x = 0.0 + x_offset,
    .y = layer,
    .distl = 0.0f,
    .distr = 0.0f,
    .exist = false,
  };
  if(!tree) {
    return tree_pos;
  }
  TreePos tree_pos_left = {0};
  float dist_left = 0.0;
  if (tree->left) {
    tree_pos_left = get_tree_pos(tree->left, stack, layer+1.0, x_offset);
    dist_left = tree_pos_left.distl + tree_pos_left.distr + 1.0;
  }
  TreePos tree_pos_right = {0};
  float dist_right = 0.0;
  if (tree->right){
    tree_pos_right = get_tree_pos(tree->right, stack, layer+1.0, x_offset + 1.0 + dist_left);
    dist_right = tree_pos_right.distl + tree_pos_right.distr + 1.0;
  }
  tree_pos.x = x_offset + dist_left;
  tree_pos.distl = dist_left;
  tree_pos.distr = dist_right;
  tree_pos.exist = true;
  stack_push(stack, CLITERAL(Vector3) {
      .x = tree_pos.x,
      .y = tree_pos.y,
      .z = (float)tree->data,
    });
  return tree_pos;
}

