/*******************************************************************************************************************************************************************
*Title			: Find Maximum
*Description		: This function finds the maximum data from the given Red Black tree.
*Prototype		: int find_maximum(tree_t **root, data_t *max);
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
			: max – Maximum data present in the tree is collected via this pointer.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "rbt.h"

tree_t* tree_maximum(tree_t *node)
{
	while (node && node->right != NULL)
		node = node->right;
	return node;
}

int find_maximum(tree_t **root, data_t *max)
{
	if (*root == NULL)
		return FAILURE;

	tree_t *max_node = tree_maximum(*root);
	if (max_node)
	{
		*max = max_node->data;
		return SUCCESS;
	}
	return FAILURE;
}
