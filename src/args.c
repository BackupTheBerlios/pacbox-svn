#include "args.h"

#include <string.h>
Args * args_new ()
{
	Args *args = malloc (sizeof (Args));
	args_init (args);	
	return args;
}

void args_init (Args *args)
{
	args->verbose = 0;
	args->ask = 0;
	args->package_list = list_new ();
}

void args_parse (Args *args, int argc,  char **argv)
{
	int i;
		
	/* Iterates through the arguments */
	for (i = 1; i < argc; ++i)
	{
		/* Checks for arguments */
		if (strcmp (argv[i], "-v") == 0)
		{
			args->verbose++;
		}
		else if (strcmp (argv[i], "-a") == 0)
		{
			args->ask = 1;
		}
		else if (argv[i][0] == '-' && strlen (argv[i]) > 2)
		{
			int j;

			for (j = 1; j < strlen (argv[i]); ++j)
			{
				if (argv[i][j] == 'v')
					args->verbose++;

				if (argv[i][j] == 'a')
					args->ask = 1;
			}
		}
		else
		{	
			/* Its a package */
			char *tmp = calloc (strlen (argv[i]), sizeof (char*));
			
			strcpy (tmp, argv[i]);
			
			list_add_node (args->package_list, 
						   node_create(tmp) );	
		}
	}
}


void args_destroy (Args *args)
{
	list_destroy (args->package_list);	
	free (args);
}
