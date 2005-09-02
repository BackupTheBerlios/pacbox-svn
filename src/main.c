#include "string_utils.h"
#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Struct for containing a config line */
typedef struct _ConfigLine {
	char left[30];
	char right[500];
} ConfigLine;

/* Prints the usage for the program */
void print_usage (const char *name);

/* Prints the helptext */
void print_help ();

/* Prints info for the compile and so forth */
void print_info ();


int main (int argc, char **argv)
{
	/* if no argument */
	if (argc == 1)
	{
		print_usage (argv[0]);
		print_help ();
	}
	else
	{
		/* Checks if the argument is a keyword */
		if (strcmp (argv[1], "info") == 0)
		{
			print_info ();
		}
		else	/* It is a package */
		{
			/* mr_echo: do your thing here! */
		}
	}
	
	return 0;
}

void print_usage (const char *name)
{
	printf ("Usage: %s [args] package\n", name);
}

void print_help ()
{
	printf ("PacBox v 0.1\n");
	printf ("\t-h\t--help\t Prints this help text\n");
	printf ("\n Keywords\n");
	printf ("\tinfo\t Prints pacbox info and other\n");
}

void print_info ()
{
	char buffer[2048];
	FILE *fd;
	LinkedList *list = malloc (sizeof (LinkedList));
	ListNode *it;	
	
	/* Creates the list */
	list_init (list);
	
	/* Opens config file for reading */
	fd = fopen ("make.conf", "r");
	
	/* Fetches the line from file
	 * and prints it to the console */
	while (fgets (buffer, sizeof (buffer), fd))
	{
		ListNode *node = malloc (sizeof (ListNode));
	
		ConfigLine *cl = malloc (sizeof (ConfigLine));

		/* Ignores empty lines */
		if (buffer[0] != '\n')
		{
			/* Splits the string on = */
			string_split (buffer, cl->left, cl->right, '=');

			node->data = cl;
			list_add_node (list, node);

		}
	}
	
	/* Prints all the configs */
	it = list->first;
	for (it = list->first; it != list->last->next; it = it->next)
	{
		printf ("%s: %s", 
				((ConfigLine *)it->data)->left, 
				((ConfigLine *)it->data)->right);
		
	}

	/* Closes the file handler */
	fclose (fd);
	
	/* Clears the list and clear the
	 * used memory */
	list_clear (list);
	free (list);
}

