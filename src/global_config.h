typedef struct GlobalConfig {
	char *cflags;			/* A string containing cflags	*/
	char *base_dir;			/* Path to the package base		*/
} GlobalConfig;

/* Sets the struct to default values */
void global_config_init (GlobalConfig *config);

/* Sets all the elements to default values */
void global_config_set_defaults (GlobalConfig *config);

/* Prints out configto stdout */
void global_config_print (GlobalConfig *config);

/* Clears the config */
void global_config_destroy (GlobalConfig *config);

