#include <stdlib.h>
#include <stdio.h>

/* Prints the usage for the program */
void print_usage (const char *name);

/* Prints the helptext */
void print_help ();

int main (int argc, char **argv)
{
	if (argc == 1)
	{
		print_usage (argv[0]);
		print_help ();
	}
	return 0;
}

void print_usage (const char *name)
{
	printf ("Usage: %s [args] package\n", name);
}

void print_help ()
{
	printf ("\t-h\t--help\t Prints this help text\n");
}
