#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

/* Struct for a node */
typedef struct _ListNode {
	struct _ListNode *prev;
	void *data;
	struct _ListNode *next;
} ListNode;

typedef struct _LinkedList {
	ListNode *first;	/* Node to the first item in the list */
	ListNode *last;		/* Node to the last item in the list */
	int num_nodes;		/* Number of nodes in the list */
} LinkedList;

/* Initiate list*/
void list_init (LinkedList *list);

/* Adds a node in the back of the list */
void list_add_node (LinkedList *list, ListNode *node);

/* Clears the list */
void list_clear (LinkedList *list);

#endif /* _LINKED_LIST_H_ */
