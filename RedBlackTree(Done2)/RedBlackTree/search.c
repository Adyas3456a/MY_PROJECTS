/**************************************************************************************************************************************************************
*Title		: Search function
*Description	: This function is used to search elements in Red Black Tree.
***************************************************************************************************************************************************************/
#include "rbt.h"

tree_t* search(tree_t *root, data_t item)
{
	if (root == NULL || root->data == item)
		return root;

	if (item < root->data)
		return search(root->left, item);
	else
		return search(root->right, item);
}
