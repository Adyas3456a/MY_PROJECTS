/**************************************************************************************************************************************************************
*Title		: main function(Driver function)
*Description	: This function is used as the driver function for all the Red Black Tree operations along with Print format function for the red-black colors
***************************************************************************************************************************************************************/
#include "rbt.h"

void print_tree(tree_t *root)
{
	if (root != NULL)
	{
		print_tree(root->left);
		printf("(%d)--(%s->%d)\n", root->data, root->color == RED ? "RED" : "BLACK", root->color);
		print_tree(root->right);
	}
}

int main()
{
	tree_t *root = NULL;
	data_t data;
	data_t minimum, maximum;
	char option;
	int operation, status;

	do
	{
		printf("\n1.Create a tree\n");
		printf("2.Display\n");
		printf("3.Search a node\n");
		printf("4.Find Maximum node in Tree\n");
		printf("5.Find Minimum node in Tree\n");
		printf("6.Deletion\n");
		printf("7.Delete Minimum node\n");
		printf("8.Delete Maximum Node\n");
		printf("9.Exit\n\n");

		printf("Enter the choice: ");
		scanf("%d", &operation);

		switch (operation)
		{
			case 1:
				do {
					printf("\nEnter the element: ");
					scanf("%d", &data);

					printf("Before Balancing Red Black Tree is:\n");
					print_tree(root);

					status = insert(&root, data);
					if (status == SUCCESS)
					{
						printf("\nNow Tree is balanced\n");
						print_tree(root);
					}
					else
					{
						printf("Insertion failed (Duplicate element)\n");
					}

					printf("\nDo u want to continue(y/n): ");
					scanf(" %c", &option);
				} while (option == 'y' || option == 'Y');
				break;

			case 2:
				printf("\nDisplay\n");
				print_tree(root);
				break;

			case 3:
				printf("\nEnter the element which you want to search from the red black tree: ");
				scanf("%d", &data);
				tree_t *node = search(root, data);
				if (node)
				{
					printf("Node %d found (%d)--(%s->%d)\n", data, node->data, node->color == RED ? "RED" : "BLACK", node->color);
				}
				else
				{
					printf("Node %d not found in the Red Black Tree\n", data);
				}
				break;

			case 4:
				if (find_maximum(&root, &maximum) == SUCCESS)
					printf("Maximum node: %d\n", maximum);
				else
					printf("Tree is empty\n");
				break;

			case 5:
				if (find_minimum(&root, &minimum) == SUCCESS)
					printf("Minimum node: %d\n", minimum);
				else
					printf("Tree is empty\n");
				break;

			case 6:
				printf("\nEnter the element to delete: ");
				scanf("%d", &data);
			
				printf("\nTree Before deleting the node:\n");
				print_tree(root);
			
				status = delete(&root, data);
				if (status == SUCCESS)
				{
					printf("\nTree After deleting the node:\n");
					print_tree(root);
				}
				else
				{
					printf("Element not found.\n");
				}
				break;
			

			case 7:
				printf("\nTree Before deleting the minimum node:\n");
				print_tree(root);
			
				status = delete_minimum(&root);
				if (status == SUCCESS)
				{
					printf("\nTree After deleting the minimum node:\n");
					print_tree(root);
				}
				else
				{
					printf("\nTree is empty or deletion failed.\n");
				}
				break;
			

			case 8:
				printf("\nTree Before deleting the maximum node:\n");
				print_tree(root);
			
				status = delete_maximum(&root);
				if (status == SUCCESS)
				{
					printf("\nTree After deleting the maximum node:\n");
					print_tree(root);
				}
				else
				{
					printf("\nTree is empty or deletion failed.\n");
				}
				break;
			

			case 9:
				printf("Exiting...\n");
				break;

			default:
				printf("Invalid choice.\n");
		}
	} while (operation != 9);

	return 0;
}
