#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include "package.h"
#include "string_utils.h"
#include "linked_list.h"


int package_install (char *name, GlobalConfig *config)
{
	Package package;
	package_init (&package);

	/* Get info */
	if (package_get_info (&package) < 0)
	{
		printf ("Error parsing package file\n");
		return -1;
	}

	/* Uncomment this to show package data 
	printf ("%s\n", package.name);
	printf ("%s\n", package.version);
	printf ("%i\n", package.release);
	printf ("%s\n", package.category);
	printf ("%s\n", package.description);
	printf ("%s\n", package.dependencies);
	printf ("%s\n", package.build_dependencies);
	printf ("%s\n", package.url); */

	if (package_is_installed (&package, config) == 0)
	{
		printf ("Package is already installed\n");
		return -1;
	}
/*
	if (package_install_deps (&package) < 0)
	{
		printf ("Problems installing dependencies\n");
		return -1;
	}
*/
	if (package_fetch (&package, config) < 0)
	{
		printf ("Problems fetching package\n");
		return -1;
	}

	if (package_build (&package, config) < 0)
	{
		printf ("Problems building package\n");
		return -1;
	}

/*	printf ("Everything is OK. Let's install it! :)\n");*/

/*	
	package_build
	package_register	
*/
	package_destroy (&package);

	return 0;
}


int package_get_info (Package *package)
{
	FILE *file;
	char *path;
	char buf[512];
	/* Size of temporary variables which will hold the result from string_split */
	char line_left[50];
	char line_right[512];

	/* TODO must get path to package file */
	path = "../example_packages/PACKAGE";

	if ((file = fopen(path, "r")) == NULL)
	{
		printf("Error opening file: %s\n", path);
		return -1;
	}

	while (fgets(buf, sizeof(buf), file))
	{
		/* Trim whitespace */
		string_trim (buf);

		/* Skip comments and empty lines */
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
		/* VERSION */
		else if (strcmp(line_left, "VERSION") == 0)
		{
			package->version = calloc (sizeof(buf), sizeof(char));
			strncpy (package->version, line_right, sizeof(buf));
		}
		/* RELEASE */
		else if (strcmp(line_left, "RELEASE") == 0)
		{
			sscanf(line_right, "%i", &package->release);
		}
		/* CATEGORY */
		else if (strcmp(line_left, "CATEGORY") == 0)
		{
			package->category = calloc (sizeof(buf), sizeof(char));
			strncpy (package->category, line_right, sizeof(buf));
		}
		/* DESCRIPTION */
		else if (strcmp(line_left, "DESCRIPTION") == 0)
		{
			package->description = calloc (sizeof(buf), sizeof(char));
			strncpy (package->description, line_right, sizeof(buf));
		}
		/* DEPENDENCIES */
		else if (strcmp(line_left, "DEPENDENCIES") == 0)
		{
			package->dependencies = calloc (sizeof(buf), sizeof(char));
			strncpy (package->dependencies, line_right, sizeof(buf));
		}
		/* BUILD_DEPENDENCIES */
		else if (strcmp(line_left, "BUILD_DEPENDENCIES") == 0)
		{
			package->build_dependencies = calloc (sizeof(buf), sizeof(char));
			strncpy (package->build_dependencies, line_right, sizeof(buf));
		}
		/* URL */
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


int package_is_installed (Package *package, GlobalConfig *config)
{
	char path[512];
	struct stat tmp;

	snprintf (path, sizeof(path), "%s/%s_%s_%i", config->db_dir, package->name, package->version,
			  									 package->release);

	if (stat (path, &tmp) == -1)
	{
		/* Path doesn't exist */
		return -1;
	}
	else
	{
		/* Path does exist */
		return 0;
	}
}


int package_install_deps (Package *package)
{
	LinkedList *list;
	
	list  = string_split_tokens (package->dependencies, " ");
	
	if (list)
	{
		int i;
		ListNode *it;

		for (it = list->first, i = 0; it != list->last->next; it = it->next, ++i)
		{
			printf ("%i: %s\n", i+1, ((char*)it->data));
		}
	}
	else
	{
		printf ("Error parsing dependencies");
	}
	/* For each dependency listed, check if it is installed.
	 * If not, install it */
	return 0;
}


int package_fetch (Package *package, GlobalConfig *config)
{
	/*TODO Make globalconfig contain command of download manager
	 *TODO Move checking of directories to some kind of startup-function
	 *TODO Currently just checking if /var/tmp/pacbox and /var/tmp/pacbox/distfiles
	 *     exists. I.e. /var/tmp must exist */
	char path[512];
	char command[1024];
	struct stat tmp;

	snprintf (path, sizeof(path), "%s", config->tmp_dir);
	if (stat (path, &tmp) == -1)
	{
		/* Path does not exist, let's create it */
		if (mkdir (path, 0755) != 0)
		{
			printf ("Error creating directory: %s\n", path);
		}
		printf ("Created directory: %s\n", path);
	}

	snprintf (path, sizeof(path), "%s/distfiles", config->tmp_dir);
	if (stat (path, &tmp) == -1)
	{
		/* Path does not exist, let's create it */
		if (mkdir (path, 0755) != 0)
		{
			printf ("Error creating directory: %s\n", path);
		}
		printf ("Created directory: %s\n", path);
	}


	/* TODO Must get filename part of url */
	snprintf (path, sizeof(path), "%s/distfiles/%s", config->tmp_dir, "nano.tar.gz");
	
	/* If file doesn't exist: fetch it */
	if (stat (path, &tmp) == -1)
	{
		snprintf (command, sizeof(command), "wget %s -O %s", package->url, path);
		system(command);
	}

	return 0;
}


int package_build (Package *package, GlobalConfig *config)
{
	char path1[512];
	char path2[512];
	char command[1024];
	struct stat tmp;

	/* EXTRACT */
	/* TODO Must get filename part of url */
	snprintf (path1, sizeof(path1), "%s/distfiles/%s", config->tmp_dir, "nano.tar.gz");

	if (stat (path1, &tmp) == -1)
	{
		printf ("File does not exist");
		return -1;
	}

	snprintf (path1, sizeof(path1), "%s/distfiles/%s", config->tmp_dir, "nano.tar.gz");
	snprintf (path2, sizeof(path2), "%s", config->tmp_dir);
	snprintf (command, sizeof(command), "tar xvpf %s -C %s", path1, path2);

	system (command);

	/* CHANGE DIR */
	/* TODO Get real extracted path. Should we use <program>-<version>? */
	snprintf (path1, sizeof(path1), "%s/nano-1.2.5", config->tmp_dir);
	if (chdir (path1) == -1)
	{
		printf ("Error changing directory\n");
		return -1;
	}

	/* CONFIGURE */
	system("./configure");

	/* MAKE */
	system("make");
	
	/* 1) Extract distfile to /var/tmp/pacbox/<package>/
	 * 2) Change dir
	 * 3) Run ./configure
	 * 4) Run make
	 */
	return 0;
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
