#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

/* Struct for a node */
typedef struct _ListNode {
	struct _ListNode *prev; /* A pointer to the previus node */
	void *data;				/* pointer to the data of the node */
	struct _ListNode *next;	/* Pointer to the next node */
} ListNode;

typedef struct _LinkedList {
	ListNode *first;	/* Node to the first item in the list */
	ListNode *last;		/* Node to the last item in the list */
	int num_nodes;		/* Number of nodes in the list */
} LinkedList;

/* Returns a new linked list */
LinkedList * list_new ();

/* Initiate list*/
void list_init (LinkedList *list);

/* Adds a node in the back of the list */
void list_add_node (LinkedList *list, ListNode *node);

/* Creates a listnode with given data */
ListNode * node_create (void *data);

/* Clears the list and removes any used memory */
void list_clear (LinkedList *list);

/* Clears the list and removes the list itself */
void list_destroy (LinkedList *list);

#endif /* _LINKED_LIST_H_ */
