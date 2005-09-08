#include "global_config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void global_config_init (GlobalConfig *config)
{
	config->cflags = 0;
	config->base_dir = 0;
	config->db_dir = 0;
	config->tmp_dir = 0;
}

void global_config_set_defaults (GlobalConfig *config)
{
	/* Don't know witch way to do this 
	 * but i'll fix it later */
	char cflags[] = "-pipe -fomit-frame-pointer";
	config->cflags = calloc (80, sizeof (char));
	strncpy (config->cflags, cflags, 75);

	config->base_dir = calloc (50, sizeof (char));
	strcpy (config->base_dir, "/usr/pacbox");

	config->db_dir = malloc (50 * sizeof (char));
	strncpy (config->db_dir, "/var/pacbox", 50);

	config->tmp_dir = malloc (50 * sizeof (char));
	strncpy (config->tmp_dir, "/var/tmp/pacbox", 50);
}

void global_config_print (GlobalConfig *config)
{
	printf ("Pacbox base dir: %s\n", config->base_dir);
	printf ("CFLAGS: %s\n", config->cflags);	
	printf ("DB Dir: %s\n", config->db_dir);
	printf ("Temp dir: %s\n", config->tmp_dir);
}

void global_config_destroy (GlobalConfig *config)
{
	free (config->cflags);
	free (config->base_dir);
	free (config->db_dir);
	free (config->tmp_dir);
}
