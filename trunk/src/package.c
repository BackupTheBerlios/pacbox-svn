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
	if (package_parse (&package, config) < 0)
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

	if (package_is_installed (&package, config) < 0)
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

	if (package_merge (&package, config) < 0)
	{
		printf ("Problems installing package\n");
		return -1;
	}

/*	
	package_build
	package_register	
*/
	package_destroy (&package);

	return 0;
}


int package_parse (Package *package, GlobalConfig *config)
{
	FILE *file;
	char *path;
	char line[1024];
	int line_length = 0;

	/* TODO must get path to package file */
	/* If we use the command find, is the syntax
	 * the same in freebsd find and linux find? */
	path = "../example_packages/PACKAGE";

	if ((file = fopen(path, "r")) == NULL)
	{
		printf("Error opening file: %s\n", path);
		return -1;
	}

	while (fgets(line, sizeof (line), file))
	{
		char *line_left;
		char *line_right;
		int line_right_len;
		
		line_length = strlen (line);

		/* Check so that length of lines is not too large */
		if (line_length == sizeof (line)-1)
		{
			printf ("Too many characters in line:\n%s", line);
			return -1;
		}
		
		/* Trim whitespace */
		string_trim (line);

		/* Skip comments and empty lines */
		if ((line[0] == '#') || (line[0] == '\n') || (line[0] == '\r'))
		{
			continue;
		}

		/* Split on = */
		string_split (line, &line_left, &line_right, '=');


		/* Save length of right part of line */
		line_right_len = strlen (line_right)+1;

		/* NAME */
		if (strcmp(line_left, "NAME") == 0)
		{
			package->name = calloc (line_right_len, sizeof(char));
			strncpy (package->name, line_right, line_right_len);
		}
		/* VERSION */
		else if (strcmp(line_left, "VERSION") == 0)
		{
			package->version = calloc (line_right_len, sizeof(char));
			strncpy (package->version, line_right, line_right_len);
		}
		/* RELEASE */
		else if (strcmp(line_left, "RELEASE") == 0)
		{
			sscanf(line_right, "%i", &package->release);
		}
		/* CATEGORY */
		else if (strcmp(line_left, "CATEGORY") == 0)
		{
			package->category = calloc (line_right_len, sizeof(char));
			strncpy (package->category, line_right, line_right_len);
		}
		/* DESCRIPTION */
		else if (strcmp(line_left, "DESCRIPTION") == 0)
		{
			package->description = calloc (line_right_len, sizeof(char));
			strncpy (package->description, line_right, line_right_len);
		}
		/* DEPENDENCIES */
		else if (strcmp(line_left, "DEPENDENCIES") == 0)
		{
			package->dependencies = calloc (line_right_len, sizeof(char));
			strncpy (package->dependencies, line_right, line_right_len);
		}
		/* BUILD_DEPENDENCIES */
		else if (strcmp(line_left, "BUILD_DEPENDENCIES") == 0)
		{
			package->build_dependencies = calloc (line_right_len, sizeof(char));
			strncpy (package->build_dependencies, line_right, line_right_len);
		}
		/* URL */
		else if (strcmp(line_left, "URL") == 0)
		{
			package->url = calloc (line_right_len, sizeof(char));
			strncpy (package->url, line_right, line_right_len);
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
		printf ("Error changing directory to \"%s\"\n", path1);
		return -1;
	}

	/* CONFIGURE */
	snprintf (command, sizeof(command), "./configure --prefix=%s/nano-1.2.5/install", config->tmp_dir);
	system(command);

	/* MAKE */
	system("make");
	
	/* 1) Extract distfile to /var/tmp/pacbox/<package>/
	 * 2) Change dir
	 * 3) Run ./configure
	 * 4) Run make
	 */
	return 0;
}


int package_merge (Package *package, GlobalConfig *config)
{
	struct stat tmp;
	char path[512];

	/* TODO Get program name-version-release instead of nano-1.2.5 */
	snprintf (path, sizeof(path), "%s/nano-1.2.5/install", config->tmp_dir);
	if (stat (path, &tmp) == -1)
	{
		/* Temporary build dir does not exist, let's create it */
		if (mkdir (path, 0755) != 0)
			printf ("Error creating install directory\n");
	}

	/* Change to build dir */
	snprintf (path, sizeof(path), "%s/nano-1.2.5", config->tmp_dir);
	if (chdir (path) == -1)
	{
		printf ("Error changing directory to \"%s\"\n", path);
		return -1;
	}

	/* Install to "fake dir" */
	system ("make install");

	/* TODO Move the files to real filesystem */

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
