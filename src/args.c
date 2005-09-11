#include "args.h"

Args * args_new ()
{
	Args *args = malloc (sizeof (Args));
	args_init (args);	
	return args;
}

static void args_init (Args *args)
{
	args->verbose = 0;
	args->ask = 0;
	args->package_list = list_new ();
}

void args_destroy (Args *args)
{
	list_destroy (args->package_list);	
	free (args);
}
