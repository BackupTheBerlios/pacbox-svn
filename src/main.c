#include "package.h"
#include "string_utils.h"
#include "linked_list.h"
#include "global_config.h"
#include "args.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Prints the usage for the program */
void print_usage (const char *name);

/* Prints the helptext */
void print_help ();

/* Prints info for the compile and so forth */
void print_info (GlobalConfig *conf);

int main (int argc, char **argv)
{
	GlobalConfig conf;
	Args *args = args_new ();
	global_config_set_defaults (&conf);
	
	/* this ocours when the user
	 * dont supply arguments */
	if (argc == 1)
	{
		print_help ();
	}
	else
	{	
		int i;
		
		/* Iterates through the arguments */
		for (i = 1; i < argc; ++i)
		{
			if (strcmp (argv[i], "-v") == 0)
				args->verbose++;
			else if (strcmp (argv[i], "-a") == 0)
				args->ask = 1;
			else
			{	/* Its a package */
				char *tmp = malloc (strlen (argv[i]) * sizeof (char));
				strcpy (tmp, argv[i]);
				list_add_node (args->package_list, 
							   node_create(tmp) );	
			}
		}
		
		if (args->verbose)
		{
			ListNode *it;
			printf ("Going to install packages:\n");
			for (it = args->package_list->first;
				 it != args->package_list->last->next;
				 it = it->next)
			{
				printf ("%s\n", (char *)it->data);
			}
		}
		
		
		/*
		 * package_install("/home/erik/Desktop/pacbox/echo/PACKAGE", &conf);
		 * */
	}
	
	global_config_destroy (&conf);
	args_destroy (args);
	return 0;
}

void print_usage (const char *name)
{
	printf ("Usage:\t%s [args] package or\n\t%s [keyword]\n\n", name, name);
}

void print_help ()
{
	printf ("%s %s\n", PACKAGE_NAME, PACKAGE_VERSION);
	printf ("Args\n");
	printf ("\t-h\t Prints this help text\n");
	printf ("\t-a\t Asks first if you want to install\n");
	printf ("\t-v\t Prints some more output\n");
	printf ("\nKeywords\n");
	printf ("\tinfo\t Prints pacbox info and other\n");
}

void print_info (GlobalConfig *conf)
{
	printf ("%s %s\n", PACKAGE_NAME, PACKAGE_VERSION);
	global_config_print (conf);
	
}

