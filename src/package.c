#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "package_parser.h"
#include "string_utils.h"
#include "linked_list.h"


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
	free (package->release);
	free (package->category);
	free (package->description);
	free (package->dependencies);
	free (package->build_dependencies);
	free (package->url);
}


/* Parses a package file */
int parse_package (const char *file)
{
	FILE *package;
	char buf[512];

	if ((package = fopen(file, "r")) == NULL)
	{
		/* No such file or directory */
		printf("Error opening file: %s", file);
		return 1;
	}

	while (fgets(buf, sizeof(buf), package))
	{
		/* Trim whitespace */
/*		string_trim (buf);*/

		/* If comment or empty line, skip it */
		if ((buf[0] == '#') || (buf[0] == '\n'))
		{
			continue;
		}

		/* Split on = */
		string_split (buf, cl->left, cl->right, '=');

	}
	
	/* Close file */
	fclose (package);

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
