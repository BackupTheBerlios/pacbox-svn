#include "linked_list.h"

#include <stdlib.h>

void list_init (LinkedList *list)
{
	/* Resets the variables */
	list->first = 0;
	list->last = 0;
	list->num_nodes = 0;
}

void list_add_node (LinkedList *list, ListNode *node)
{
	/* Sets default values to the node */
	node->prev = 0;
	node->next = 0;

	/* If the list is empty */
	if (list->first == 0)
	{
		list->first = node;
		list->last = node;
	}
	else /* The list is not empty*/
	{
		list->last->next = node;
		node->prev = list->last;
		list->last = node;
	}
	
	/* increaces the node counter */
	list->num_nodes++;
}

void list_clear (LinkedList *list)
{
	/* If there is just one item */
	if (list->first == list->last)
	{
		free (list->first->data);
		free (list->first);

		list->first = 0;
		list->last = 0;
	}
	else /* More then one */
	{
		ListNode *tmp;
		ListNode *next;
		
		tmp = list->first;
		
		/* Loops through the node list 
		 * and removes the data and the 
		 * node */
		while (tmp != list->last->next)
		{
			next = tmp->next;
			free (tmp->data);
			free (tmp);	
			tmp = next;
		}
		
		list->first = 0;
		list->last = 0;
	}
	
	/* Resets the counter */
	list->num_nodes = 0;
}

void list_destry (LinkedList *list)
{
	list_clear (list);
	free (list);
	list = 0;
}
