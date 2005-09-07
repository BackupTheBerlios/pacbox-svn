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
int package_install (char *name, GlobalConfig *config);

/* Parse packagefile and put into struct */
int package_get_info (Package *package);

/* Check if a package already is installed */
int package_is_installed (Package *package, GlobalConfig *config);

/* Check and install deps for a package */
int package_install_deps (Package *package);

/* Fetch a package from the Internet */
int package_fetch (Package *package, GlobalConfig *config);

/* Builds a package */
int package_build (Package *package);

/* Init's a struct of type Package */
void package_init (Package *package);

/* Destoy's and free's memory for a Package struct */
void package_destroy (Package *package);

#endif /* _PACKAGE_H_ */
