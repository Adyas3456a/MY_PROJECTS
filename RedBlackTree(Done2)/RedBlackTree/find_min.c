/*******************************************************************************************************************************************************************
*Title			: Find Minimum
*Description		: This function finds the minimum data from the given Red Black tree.
*Prototype		: int find_minimum(tree_t **root, data_t *min);
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
			: min – Minimum data present in the tree is collected via this pointer.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "rbt.h"

tree_t* tree_minimum(tree_t *node)
{
	while (node && node->left != NULL)
		node = node->left;
	return node;
}

int find_minimum(tree_t **root, data_t *min)
{
	if (*root == NULL)
		return FAILURE;

	tree_t *min_node = tree_minimum(*root);
	if (min_node)
	{
		*min = min_node->data;
		return SUCCESS;
	}
	return FAILURE;
}
