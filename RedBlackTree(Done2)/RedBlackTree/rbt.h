/***************************************************************************************************************************************************************
*Title		: This the header file for the Red Black Tree
****************************************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#ifndef RBT_H
#define RBT_H
#define SUCCESS 0
#define FAILURE -1

typedef int data_t;

typedef enum { RED, BLACK } color_t;

typedef struct node
{
	data_t data;
	color_t color;
	struct node *left, *right, *parent;
} tree_t;

// Function Prototypes
tree_t* create_node(data_t item);
int insert(tree_t **root, data_t item);
int delete(tree_t **root, data_t item);
tree_t* search(tree_t *root, data_t item);

int find_minimum(tree_t **root, data_t *min);
int find_maximum(tree_t **root, data_t *max);
tree_t* tree_minimum(tree_t *node);
tree_t* tree_maximum(tree_t *node);

int delete_minimum(tree_t **root);
int delete_maximum(tree_t **root);

void rotate_left(tree_t **root, tree_t *x);
void rotate_right(tree_t **root, tree_t *y);
void fix_insertion(tree_t **root, tree_t *z);
void fix_deletion(tree_t **root, tree_t *x);

#endif
