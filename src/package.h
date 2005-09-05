#ifndef _PACKAGE_H_
#define _PACKAGE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "global_config.h"


typedef struct Package {
	char *name;
	char *version;
	int  release;
	char *category;
	char *description;
	char *dependencies;
	char *build_dependencies;
	char *url;
} Package;


/* Main function for installing packages */
void package_install (char *name, GlobalConfig *config);

/* Parse packagefile and put into struct */
int package_get_info (Package *package);




/* Init's a struct of type Package */
void package_init (Package *package);

/* Destoy's and free's memory for a Package struct */
void package_destroy (Package *package);


/* Parses a package file */
int parse_package (const char *file);

/*
 *	returns substring from str, using start and len
 *	WARNING: return object must be free'd
 */
char *substr (const char *from, int start, int len);

#endif /* _PACKAGE_H_ */
