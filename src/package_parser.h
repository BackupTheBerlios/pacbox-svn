#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Parses a package file */
int parse_package (const char *file);

/*
 *	returns substring from str, using start and len
 *	WARNING: return object must be free'd
 */
char *substr (const char *from, int start, int len);
