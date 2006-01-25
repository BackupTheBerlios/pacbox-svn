/***************************************************************************
 *   Copyright (C) 2006 by Johan Grahn   *
 *   johan@cgeek.net   *
 *                                                                         *
 *   Permission is hereby granted, free of charge, to any person obtaining *
 *   a copy of this software and associated documentation files (the       *
 *   "Software"), to deal in the Software without restriction, including   *
 *   without limitation the rights to use, copy, modify, merge, publish,   *
 *   distribute, sublicense, and/or sell copies of the Software, and to    *
 *   permit persons to whom the Software is furnished to do so, subject to *
 *   the following conditions:                                             *
 *                                                                         *
 *   The above copyright notice and this permission notice shall be        *
 *   included in all copies or substantial portions of the Software.       *
 *                                                                         *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       *
 *   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    *
 *   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. *
 *   IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR     *
 *   OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, *
 *   ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR *
 *   OTHER DEALINGS IN THE SOFTWARE.                                       *
 ***************************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <getopt.h>

/**
 * This defines the path for the global config
 * Going to change this when the program uses 
 * /etc for config-dir 
 */
#define GLOBAL_CONFIG "config"

/**
 * Struct that represents any option given at 
 * command-line 
 */
struct options {
	int verbose; /* toogles verbose mode */
};

/**
 * Reads the config-file and fetches the value 
 * for the property name 
 */
int default_config_read (const char *_name);

/**
 * Prints usage information for the program 
 * to the stderr output 
 */
static void 
usage ();

int 
main (int argc, char **argv)
{
	char tmp_ch;
	struct options opt = { 0 };
	
	/* Checks if there are no args */
	if (argc == 1) {
		usage();
		exit(1);
	}
	
	/**
	 * Using getopt(3) to capture all options that is
	 * given to the program 
	 */
	while ((tmp_ch = getopt(argc, argv, "v")) != -1) {
		switch (tmp_ch) {
			case 'v':
				printf ("Setting verbose ON\n");
				opt.verbose = 1;
		}
	}

	printf ("Index: %d", optind);

	return 0;
}

static void 
usage ()
{
	fprintf(stderr, "usage pacbox [-v] package\n\n");
	fprintf(stderr, "options:\n");
	fprintf(stderr, "\t-v\tSets verbose logging\n");
}
