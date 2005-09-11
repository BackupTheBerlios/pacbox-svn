#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

#include <stdlib.h>
#include "linked_list.h"

/* Struct containg all the 
 * arguments from the command-line */
typedef struct {
	int			verbose;		/* Sets verbose output */
	int			ask;			/* The program should ask first */
	int			pretend;		/* The program just shows the packages */
	LinkedList	*package_list;	/* A list of packages */
} Args;

/* Creates a new args struct */ 
Args * args_new ();

/* Sets struct to default values */
void args_init (Args *args);

/* Destroys the struct */
void args_destroy (Args *args);

#endif 
