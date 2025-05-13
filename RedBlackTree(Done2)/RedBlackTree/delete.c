/*******************************************************************************************************************************************************************
*Title			: Deletion
*Description		: This function performs deleting of the given data from the given Red Black tree.
*Prototype		: int delete(tree_t **root, data_t item); 
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
			: item – Data to be deleted from the Red Black tree.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "rbt.h"

tree_t* bst_delete(tree_t *root, data_t item, tree_t **deleted_node, tree_t **fix_node, int *deleted_color)
{
	if (root == NULL)
		return root;

	if (item < root->data)
		root->left = bst_delete(root->left, item, deleted_node, fix_node, deleted_color);
	else if (item > root->data)
		root->right = bst_delete(root->right, item, deleted_node, fix_node, deleted_color);
	else
	{
		*deleted_node = root;
		*deleted_color = root->color;

		if (root->left == NULL)
		{
			tree_t *temp = root->right;
			*fix_node = temp;
			if (temp) temp->parent = root->parent;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			tree_t *temp = root->left;
			*fix_node = temp;
			if (temp) temp->parent = root->parent;
			free(root);
			return temp;
		}
		else
		{
			tree_t *min = tree_minimum(root->right);
			root->data = min->data;
			root->right = bst_delete(root->right, min->data, deleted_node, fix_node, deleted_color);
		}
	}
	return root;
}

int delete(tree_t **root, data_t item)
{
	tree_t *deleted = NULL;
	tree_t *fix_node = NULL;
	int deleted_color = BLACK;

	*root = bst_delete(*root, item, &deleted, &fix_node, &deleted_color);

	if (deleted)
	{
		if (deleted_color == BLACK)
			fix_deletion(root, fix_node);
		return SUCCESS;
	}
	else
	{
		return FAILURE;
	}
}

void fix_deletion(tree_t **root, tree_t *x)
{
	while (x != *root && x && x->color == BLACK)
	{
		if (x->parent && x == x->parent->left)
		{
			tree_t *w = x->parent->right;

			if (w && w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				rotate_left(root, x->parent);
				w = x->parent->right;
			}

			if (w && (!w->left || w->left->color == BLACK) &&
				    (!w->right || w->right->color == BLACK))
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w && (!w->right || w->right->color == BLACK))
				{
					if (w->left) w->left->color = BLACK;
					w->color = RED;
					rotate_right(root, w);
					w = x->parent->right;
				}
				if (w) w->color = x->parent->color;
				x->parent->color = BLACK;
				if (w && w->right) w->right->color = BLACK;
				rotate_left(root, x->parent);
				x = *root;
			}
		}
		else if (x->parent)
		{
			tree_t *w = x->parent->left;

			if (w && w->color == RED)
			{
				w->color = BLACK;
				x->parent->color = RED;
				rotate_right(root, x->parent);
				w = x->parent->left;
			}

			if (w && (!w->left || w->left->color == BLACK) &&
				    (!w->right || w->right->color == BLACK))
			{
				w->color = RED;
				x = x->parent;
			}
			else
			{
				if (w && (!w->left || w->left->color == BLACK))
				{
					if (w->right) w->right->color = BLACK;
					w->color = RED;
					rotate_left(root, w);
					w = x->parent->left;
				}
				if (w) w->color = x->parent->color;
				x->parent->color = BLACK;
				if (w && w->left) w->left->color = BLACK;
				rotate_right(root, x->parent);
				x = *root;
			}
		}
		else
		{
			break;
		}
	}

	if (x)
		x->color = BLACK;
}
