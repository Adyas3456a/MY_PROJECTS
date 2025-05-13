/*******************************************************************************************************************************************************************
*Title			: Delete Minimum
*Description		: This function deletes the minimum data from the given Red Black tree.
*Prototype		: int delete_minimum(tree_t **root);
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "rbt.h"

// We will use delete() to remove the minimum node
int delete_minimum(tree_t **root)
{
	if (*root == NULL)
		return FAILURE;

	tree_t *min_node = tree_minimum(*root);
	if (min_node == NULL)
		return FAILURE;

	return delete(root, min_node->data);
}
