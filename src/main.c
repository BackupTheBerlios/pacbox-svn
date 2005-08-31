#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Prints the usage for the program */
void print_usage (const char *name);

/* Prints the helptext */
void print_help ();

/* Prints info for the compile and so forth */
void print_info ();

/* Returns the position of the given character 
 * If not found the pointer to the first character
 * is returned
 */
char * string_find (char *str, char ch);


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
	printf ("\tinfo\t Prints compiler info and other\n");
}

void print_info ()
{
	/* A static buffer to read a string 
	 * line in to 
	 */
	char buffer[2048];
	
	/* Opens config file for reading */
	FILE *fd = fopen ("make.conf", "r");
	
	/* Fetches the line from file
	 * and prints it to the console
	 */
	while (fgets (buffer, sizeof (buffer), fd))
	{
		char right[512];
		char left[100];
		char *tmp = string_find (buffer, '=');
		strncpy (right, tmp + 1, sizeof (right));
		*tmp = '\0';
		printf ("%s: %s", buffer, right);

	}
	
	/* Closes the file handler */
	fclose (fd);
}

char* string_find (char *str, char ch)
{
	int length = strlen (str);
	char *ptr = str;
	int i;
	
	/* Loops through the string */
	for (i = 0; i < length; ++i)
	{
		if (str[i] == ch)
			ptr = &str[i];
	}

	return ptr;
}
