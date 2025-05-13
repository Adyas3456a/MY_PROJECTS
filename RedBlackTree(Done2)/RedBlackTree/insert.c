/*******************************************************************************************************************************************************************
*Title			: Insertion
*Description		: This function performs inserting the new data into the given Red Black tree.
*Prototype		: int insert(tree_t **root, data_t item);
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
			: item – New data to be inserted into the Red Black tree.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "rbt.h"

// Create a new node
tree_t* create_node(data_t item)
{
    tree_t *new_node = (tree_t *)malloc(sizeof(tree_t));
    new_node->data = item;
    new_node->color = RED;
    new_node->left = new_node->right = new_node->parent = NULL;
    return new_node;
}

// Perform left rotation
void rotate_left(tree_t **root, tree_t *x)
{
    tree_t *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

// Perform right rotation
void rotate_right(tree_t **root, tree_t *y)
{
    tree_t *x = y->left;
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    x->parent = y->parent;
    if (y->parent == NULL)
        *root = x;
    else if (y == y->parent->right)
        y->parent->right = x;
    else
        y->parent->left = x;

    x->right = y;
    y->parent = x;
}

// Fix insertion violations
void fix_insertion(tree_t **root, tree_t *z)
{
    while (z->parent != NULL && z->parent->color == RED)
    {
        tree_t *parent = z->parent;
        tree_t *grandparent = parent->parent;

        if (parent == grandparent->left)
        {
            tree_t *uncle = grandparent->right;
            if (uncle && uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }
            else
            {
                if (z == parent->right)
                {
                    rotate_left(root, parent);
                    z = z->left;
                }
                rotate_right(root, grandparent);
                z->parent->color = BLACK;
                if (z->parent->left) z->parent->left->color = RED;
                if (z->parent->right) z->parent->right->color = RED;
            }
        }
        else
        {
            tree_t *uncle = grandparent->left;
            if (uncle && uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;
                z = grandparent;
            }
            else
            {
                if (z == parent->left)
                {
                    rotate_right(root, parent);
                    z = z->right;
                }
                rotate_left(root, grandparent);
                z->parent->color = BLACK;
                if (z->parent->left) z->parent->left->color = RED;
                if (z->parent->right) z->parent->right->color = RED;
            }
        }
    }

    while ((*root)->parent != NULL)
        *root = (*root)->parent;
    (*root)->color = BLACK;
}

// Insert node
int insert(tree_t **root, data_t item)
{
    tree_t *z = create_node(item);
    tree_t *y = NULL;
    tree_t *x = *root;

    while (x != NULL)
    {
        y = x;
        if (z->data < x->data)
            x = x->left;
        else if (z->data > x->data)
            x = x->right;
        else
            return FAILURE; // Duplicates not allowed
    }

    z->parent = y;

    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fix_insertion(root, z);
    return SUCCESS;
}
