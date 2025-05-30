#include <stdbool.h>
#include "tree_hugger.h"
#include "tree.h"
#include "stb_ds.h"
#include <stddef.h>
#include <stdio.h>

#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

void print_hash_map(TreeMap *tree_map)
{
    for (size_t i = 0; i < hmlen(tree_map); ++i) {
        printf("key: %d, NodePos.x: %f, NodePos.y: %f\n", tree_map[i].key->data, tree_map[i].value.x, tree_map[i].value.y);
    }
}

float max_layer(TreeMap *tree_map)
{
    float max = 0.0f;
    for (size_t i = 0; i < hmlen(tree_map); ++i) {
        max = tree_map[i].value.y > max ? tree_map[i].value.y : max;
    }
    return max + 1.0f;
}
void normalize_values(TreeMap *tree_map, float max_x, float max_y)
{
    if(!tree_map){
        return;
    }
    for (size_t i = 0; i < hmlen(tree_map); ++i) {
        tree_map[i].value.x += 1.0f;
        tree_map[i].value.x /= (max_x + 1.0f);
        tree_map[i].value.y += 1.0f;
        tree_map[i].value.y /= (max_y + 1.0f);
    }
}

TreePos get_tree_pos(Node* tree, TreeMap** tree_map, float layer, float x_offset){
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
    tree_pos_left = get_tree_pos(tree->left, tree_map, layer+1.0, x_offset);
    dist_left = tree_pos_left.distl + tree_pos_left.distr + 1.0;
  }
  TreePos tree_pos_right = {0};
  float dist_right = 0.0;
  if (tree->right){
    tree_pos_right = get_tree_pos(tree->right, tree_map, layer+1.0, x_offset + 1.0 + dist_left);
    dist_right = tree_pos_right.distl + tree_pos_right.distr + 1.0;
  }
  tree_pos.x = x_offset + dist_left;
  tree_pos.distl = dist_left;
  tree_pos.distr = dist_right;
  tree_pos.exist = true;
  hmput(*tree_map, tree, tree_pos);
  return tree_pos;
}

TreeMap* calc_tree_poses(Node* tree, float layer, float* max_radius) {
  TreeMap* tree_map = NULL;
  TreePos tree_pos = get_tree_pos(tree, &tree_map, layer, 0.0);
  float max_x = tree_pos.distl + 1.0f + tree_pos.distr;
  float max_y = max_layer(tree_map);
  normalize_values(tree_map, max_x, max_y);
  *max_radius = 1.0/max_x;
  return tree_map;
}

void get_edges_aux(Node *tree, Edge** edges){
  if (tree->left) {
    Edge edge = {
        .start = tree,
        .goal = tree->left,
    };
    arrput(*edges, edge);
    get_edges_aux(tree->left, edges);
  }
  if (tree->right) {
    Edge edge = {
        .start = tree,
        .goal = tree->right,
    };
    arrput(*edges, edge);
    get_edges_aux(tree->left, edges);
  }
}

Edge *get_edges(Node *tree) {
  Edge* edges = NULL;
  if(tree)
    get_edges_aux(tree, &edges);
  return edges;
}

Edge * get_edges_iter(Node *tree) {
  Edge* edges = NULL;
  if(tree) {
    Stack* stack = create_stack();
    stack_push(stack, tree);
    while(!is_empty(stack)) {
      Node* node = stack_pop(stack);
      if (node) {
        if (node->left) {
          Edge edge = {
            .start = node,
            .goal = node->left,
          };
          arrput(edges, edge);
          stack_push(stack, node->left);
        }
        if (node->right) {
          Edge edge = {
            .start = node,
            .goal = node->left,
          };
          arrput(edges, edge);
          stack_push(stack, node->right);
        }
      }
    }
  }
  return edges;
}

EdgeCoords* get_edge_coords(Edge* edges, TreeMap* tree_map) {
  EdgeCoords* edge_coords = NULL;
  for (size_t i = 0; i < arrlen(edges); i++) {
    Node* key_start = edges[i].start;
    Node* key_goal = edges[i].goal;
    int start_pos = hmgeti(tree_map, key_start);
    int goal_pos = hmgeti(tree_map, key_goal);
    if (start_pos >= 0 && goal_pos >= 0) {
      TreePos start_pos_node = tree_map[start_pos].value;
      TreePos goal_pos_node = tree_map[goal_pos].value;
      arrput(edge_coords, ((EdgeCoords){
          .x1 = start_pos_node.x,
          .y1 = start_pos_node.y,
          .x2 = goal_pos_node.x,
          .y2 = goal_pos_node.y,
          }));
    }
  }
  return edge_coords;
}


