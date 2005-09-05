#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "package.h"
#include "string_utils.h"


void package_install (char *name, GlobalConfig *config)
{
	Package package;
	package_init (&package);

	/* Get info */
	if (package_get_info (&package) > 0)
	{
		printf ("Error parsing package file");
	}

	printf ("%s\n", package.name);
	printf ("%s\n", package.version);
	printf ("%i\n", package.release);
	printf ("%s\n", package.category);
	printf ("%s\n", package.description);
	printf ("%s\n", package.dependencies);
	printf ("%s\n", package.build_dependencies);
	printf ("%s\n", package.url);

	/*
	package_get_info
	package_installed
	package_check_deps
	package_build
	package_register	
	*/
	package_destroy (&package);
}


int package_get_info (Package *package)
{
	FILE *file;
	char *path;
	char buf[512];
	/* Size of temporary pointers which will hold the result from string_split */
	char line_left[50];
	char line_right[512];

	/* TODO must get path to package file */
	path = "/home/erik/Desktop/pacbox/PACKAGE";


	if ((file = fopen(path, "r")) == NULL)
	{
		printf("Error opening file: %s", path);
		return 1;
	}


	while (fgets(buf, sizeof(buf), file))
	{
		/* Trim whitespace */
		string_trim (buf);

		if ((buf[0] == '#') || (buf[0] == '\n'))
		{
			continue;
		}

		/* Split on = */
		string_split (buf, line_left, line_right, '=');


		/* NOTE: Memory allocation below for members of package struct will
		 * be for whole line since we dont know size of only right part */

		/* NAME */
		if (strcmp(line_left, "NAME") == 0)
		{
			package->name = calloc (sizeof(buf), sizeof(char));
			strncpy (package->name, line_right, sizeof(buf));
		}
		else if (strcmp(line_left, "VERSION") == 0)
		{
			package->version = calloc (sizeof(buf), sizeof(char));
			strncpy (package->version, line_right, sizeof(buf));
		}
		else if (strcmp(line_left, "RELEASE") == 0)
		{
			/* TODO How to get release number into struct? */
			/* package->release = (int *) line_right; */
			package->release = 1;
		}
		else if (strcmp(line_left, "CATEGORY") == 0)
		{
			package->category = calloc (sizeof(buf), sizeof(char));
			strncpy (package->category, line_right, sizeof(buf));
		}
		else if (strcmp(line_left, "DESCRIPTION") == 0)
		{
			package->description = calloc (sizeof(buf), sizeof(char));
			strncpy (package->description, line_right, sizeof(buf));
		}
		else if (strcmp(line_left, "DEPENDENCIES") == 0)
		{
			package->dependencies = calloc (sizeof(buf), sizeof(char));
			strncpy (package->dependencies, line_right, sizeof(buf));
		}
		else if (strcmp(line_left, "BUILD_DEPENDENCIES") == 0)
		{
			package->build_dependencies = calloc (sizeof(buf), sizeof(char));
			strncpy (package->build_dependencies, line_right,
					 sizeof(buf));
		}
		else if (strcmp(line_left, "URL") == 0)
		{
			package->url = calloc (sizeof(buf), sizeof(char));
			strncpy (package->url, line_right, sizeof(buf));
		}
			
	}

	
	/* Close file */
	fclose (file);

	return 0;
}


/*
 *	returns substring from str, using start and len
 *	WARNING: return object must be free'd
 */
char *substr (const char *str, int start, int len)
{
	int i = 0;
	char *tmp;
	tmp = (char *) malloc(len+1);

	for (i=0; i<len; i++)
	{
		tmp[i] = str[start+i];
	}
	tmp[len] = '\0';

	return tmp;
}


void package_init (Package *package)
{
	package->name = 0;
	package->version = 0;
	package->release = 0;
	package->category = 0;
	package->description = 0;
	package->dependencies = 0;
	package->build_dependencies = 0;
	package->url = 0;
}


void package_destroy (Package *package)
{
	free (package->name);
	free (package->version);
	free (package->category);
	free (package->description);
	free (package->dependencies);
	free (package->build_dependencies);
	free (package->url);
}
