#include "kdtree.h"
#include "sort.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

struct node {
  // Index of this node's point in the corresponding 'indexes' array.
  int point_index;

  // Axis along which this node has been splot.
  int axis;

  // The left child of the node; NULL if none.
  struct node *left;

  // The right child of the node; NULL if none.
  struct node *right;
};

struct kdtree {
  int d;
  const double *points;
  struct node* root;
};

int cmp_axis(const void *a, const void *b, void *arg) {
  void **args = (void**)arg;
  int axis = *(int*)args[0];
  int d = *(int*)args[1];
  const double *points = (const double*)args[2];
  
  const int ia = *(const int*)a;
  const int ib = *(const int*)b;
  
  double va = points[ia * d + axis];
  double vb = points[ib * d + axis];
  
  if (va < vb) return -1;
  if (va > vb) return 1;
  return 0;
}

struct node* kdtree_create_node(int d, const double *points,
                                int depth, int n, int *indexes) {
  if (n == 0) {
    return NULL;
  }
  
  int axis = depth % d;
  
  void *args[3];
  args[0] = &axis;
  args[1] = &d;
  args[2] = (void*)points;
  
  hpps_quicksort(indexes, n, sizeof(int), cmp_axis, args);
  
  int median = n / 2;
  
  struct node *node = malloc(sizeof(struct node));
  node->point_index = indexes[median];
  node->axis = axis;
  node->left = kdtree_create_node(d, points, depth + 1, median, indexes);
  node->right = kdtree_create_node(d, points, depth + 1, n - median - 1, indexes + median + 1);
  
  return node;
}

struct kdtree *kdtree_create(int d, int n, const double *points) {
  struct kdtree *tree = malloc(sizeof(struct kdtree));
  tree->d = d;
  tree->points = points;

  int *indexes = malloc(sizeof(int) * n);

  for (int i = 0; i < n; i++) {
    indexes[i] = i;
  }

  tree->root = kdtree_create_node(d, points, 0, n, indexes);

  free(indexes);

  return tree;
}

void kdtree_free_node(struct node *node) {
  if (node == NULL) {
    return;
  }
  
  kdtree_free_node(node->left);
  kdtree_free_node(node->right);
  free(node);
}

void kdtree_free(struct kdtree *tree) {
  kdtree_free_node(tree->root);
  free(tree);
}

void kdtree_knn_node(const struct kdtree *tree, int k, const double* query,
                     int *closest, double *radius,
                     const struct node *node) {
  if (node == NULL) {
    return;
  }
  
  int d = tree->d;
  const double *points = tree->points;
  
  if (insert_if_closer(k, d, points, closest, query, node->point_index)) {
    double max_dist = 0;
    for (int i = 0; i < k; i++) {
      if (closest[i] != -1) {
        double dist = distance(d, query, &points[closest[i] * d]);
        if (dist > max_dist) {
          max_dist = dist;
        }
      }
    }
    *radius = max_dist;
  }
  
  int axis = node->axis;
  double node_coord = points[node->point_index * d + axis];
  double query_coord = query[axis];
  
  struct node *first_child, *second_child;
  
  if (query_coord < node_coord) {
    first_child = node->left;
    second_child = node->right;
  } else {
    first_child = node->right;
    second_child = node->left;
  }
  
  kdtree_knn_node(tree, k, query, closest, radius, first_child);
  
  if (fabs(query_coord - node_coord) < *radius) {
    kdtree_knn_node(tree, k, query, closest, radius, second_child);
  }
}

int* kdtree_knn(const struct kdtree *tree, int k, const double* query) {
  int* closest = malloc(k * sizeof(int));
  double radius = INFINITY;

  for (int i = 0; i < k; i++) {
    closest[i] = -1;
  }

  kdtree_knn_node(tree, k, query, closest, &radius, tree->root);

  return closest;
}

void kdtree_svg_node(double scale, FILE *f, const struct kdtree *tree,
                     double x1, double y1, double x2, double y2,
                     const struct node *node) {
  if (node == NULL) {
    return;
  }

  double coord = tree->points[node->point_index*2+node->axis];
  if (node->axis == 0) {
    // Split the X axis, so vertical line.
    fprintf(f, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1\" stroke=\"black\" />\n",
            coord*scale, y1*scale, coord*scale, y2*scale);
    kdtree_svg_node(scale, f, tree,
                    x1, y1, coord, y2,
                    node->left);
    kdtree_svg_node(scale, f, tree,
                    coord, y1, x2, y2,
                    node->right);
  } else {
    // Split the Y axis, so horizontal line.
    fprintf(f, "<line x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\" stroke-width=\"1\" stroke=\"black\" />\n",
            x1*scale, coord*scale, x2*scale, coord*scale);
    kdtree_svg_node(scale, f, tree,
                    x1, y1, x2, coord,
                    node->left);
    kdtree_svg_node(scale, f, tree,
                    x1, coord, x2, y2,
                    node->right);
  }
}

void kdtree_svg(double scale, FILE* f, const struct kdtree *tree) {
  assert(tree->d == 2);
  kdtree_svg_node(scale, f, tree, 0, 0, 1, 1, tree->root);
}
