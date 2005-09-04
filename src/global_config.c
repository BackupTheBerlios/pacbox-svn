#include "global_config.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void global_config_init (GlobalConfig *config)
{
	config->cflags = 0;
	config->base_dir = 0;
}

void global_config_set_defaults (GlobalConfig *config)
{
	/* Don't know witch way to do this 
	 * but i'll fix it later */
	char cflags[] = "-pipe -fomit-frame-pointer";
	config->cflags = calloc (strlen (cflags), sizeof (char));
	strcpy (config->cflags, cflags);

	config->base_dir = calloc (50, sizeof (char));
	strcpy (config->base_dir, "/usr/pacbox");
}

void global_config_print (GlobalConfig *config)
{
	printf ("Pacbox base dir: %s\n", config->base_dir);
	printf ("CFLAGS: %s\n", config->cflags);	
}

void global_config_destroy (GlobalConfig *config)
{
	free (config->cflags);
	free (config->base_dir);
}
