#include "string_utils.h"
#include "linked_list.h"
#include "global_config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define PACKAGE_VERSION "0.0.1"

/* Prints the usage for the program */
void print_usage (const char *name);

/* Prints the helptext */
void print_help ();

/* Prints info for the compile and so forth */
void print_info (GlobalConfig *conf);

int main (int argc, char **argv)
{
	GlobalConfig conf;
	
	global_config_set_defaults (&conf);
	
	/* if no argument */
	if (argc == 1)
	{
		print_usage (argv[0]);
		print_help ();
	}
	else
	{
		/* TODO: This suxs, fix it! */

		/* Checks if the argument is a keyword */
		if (strcmp (argv[1], "info") == 0)
		{
			print_info (&conf);
		}
		/* This is a verry ugly hack, but i don't know any better
		 * yet */
		else if (argv[1][0] == '-' || (argv[1][0] == '-' && argv[1][1] == '-'))
		{
			if (strcmp (argv[1], "-h") == 0 || strcmp (argv[1], "--help") == 0)
				print_help ();
		}
		else	
		{
			/* Not a valid package or keyword */
			printf ("Not a valid keyword/package\n");
		}
	}
	
	global_config_destroy (&conf);
	return 0;
}

void print_usage (const char *name)
{
	printf ("Usage:\t%s [args] package or\n\t%s [keyword]\n\n", name, name);
}

void print_help ()
{
	printf ("Args\n");
	printf ("\t-h\t--help\t Prints this help text\n");
	printf ("\n Keywords\n");
	printf ("\tinfo\t Prints pacbox info and other\n");
}

void print_info (GlobalConfig *conf)
{
	printf ("%s %s\n", PACKAGE_NAME, PACKAGE_VERSION);
	global_config_print (conf);
	
}

