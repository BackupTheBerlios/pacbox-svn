#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "package_parser.h"

/* Parses a package file */
int parse_package (const char *file)
{
	FILE *package;
	char buf[512];
/*	int i = 0; */

	if ((package = fopen(file, "r")) == NULL)
	{
		/* No such file or directory */
		printf("Error opening file: %s", file);
		return 1;
	}

	while (fgets(buf, sizeof(buf), package))
	{
		/* Trim whitespace */
		/* TODO */

		/* If comment or empty line, skip it */
		if ((buf[0] == '#') || (buf[0] == '\n'))
		{
			continue;
		}

		printf(buf);

		/* Get the stuff */
/*		for (i=0; i<strlen(buf); i++)
		{
			if (buf[i] == '=')
			{
				char *tmp;

				* Key *
				tmp = substr (buf, 0, i);
				printf(tmp);
				free(tmp);

				* Value *
				tmp = substr (buf, i+1, strlen(buf));
				printf(tmp);
				free(tmp);
			}
		}*/
	}
	
	fclose(package);
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
