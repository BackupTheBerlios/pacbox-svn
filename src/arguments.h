#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_

/* Max number of argument packages */
#define MAX_PACKAGES 50
/* Old type
 * Deprecated! */
typedef struct Args {
	int verbose;
	int ask;
	char **packages;
	int num_packages;
} Args;

/* Struct containg all the 
 * arguments from the command-line */
typedef struct Arguments {
	int		verbose;		/* Sets verbose output */
	int		ask;			/* Is the programshould ask first */
	char	**packages;		/* Array of package strings */
	int		num_packages;	/* Contains how many packages */
} Arguments;

#endif 
