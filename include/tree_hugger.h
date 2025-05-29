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

typedef struct TreeMap {
    Node *key;
    TreePos value;
} TreeMap;

typedef struct Edge {
  Node* start;
  Node* goal;
} Edge;

typedef struct EdgeCoords {
  float x1, y1, x2, y2;
} EdgeCoords;

TreeMap* calc_tree_poses(Node* tree, float layer, float* max_radius);
void print_hash_map(TreeMap *tree_map);

Edge* get_edges(Node* tree);
//EdgeCoords *get_edge_coords(Edge *edges, TreeMap *tree_map)

#endif // TREE_HUGGER_H_
