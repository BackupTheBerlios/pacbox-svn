#include "package.h"
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

typedef struct Args {
	int verbose;
	int ask;
} Args;

int main (int argc, char **argv)
{
	GlobalConfig conf;
	Args args = {0, 0};
	global_config_set_defaults (&conf);

	if (argc == 1)
	{
		print_help ();
	}
	else
	{
		int it;
		
		if (argc == 2)
		{
			if (strcmp (argv[1], "info") == 0)
				print_info (&conf);
		}
		else /* argc > 2 */
		{
			for (it = 1; it < argc; ++it)
			{
				/* It is a argument */
				if (strlen (argv[it]) == 2)	
				{
					if (argv[it][1] == 'v')
						args.verbose++;
				
					if (argv[it][1] == 'a')
						args.ask = 1; 
				}
			}

			if (args.verbose > 0)
			{
				printf ("Using verbose: ON\n");
			}
			
			if (args.ask == 1)
			{
				char c;
				printf ("Want to install these packages? [Y/n] ");
				scanf ("%c", &c);
			
				if (c == 'y' || c == 'Y')
				{	
					printf ("Installing....\n");
				}
			}
			package_install("/home/erik/Desktop/pacbox/echo/PACKAGE", &conf);
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

