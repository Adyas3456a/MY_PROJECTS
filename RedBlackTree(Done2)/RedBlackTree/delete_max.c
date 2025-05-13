/*******************************************************************************************************************************************************************
*Title			: Delete Maximum
*Description		: This function deletes the maximum data from the given Red Black tree.
*Prototype		: int delete_maximum(tree_t **root);
*Input Parameters	: root – Pointer to the root node of the Red Black tree.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "rbt.h"

// We will use delete() to remove the maximum node
int delete_maximum(tree_t **root)
{
	if (*root == NULL)
		return FAILURE;

	tree_t *max_node = tree_maximum(*root);
	if (max_node == NULL)
		return FAILURE;

	return delete(root, max_node->data);
}
