#include "string.h"

#include <string.h>

char* string_find (char *str, char ch)
{
	int length = strlen (str);
	char *ptr = str;
	int i;
	
	/* Loops through the string */
	for (i = 0; i < length; ++i)
	{
		if (str[i] == ch)
			ptr = &str[i];
	}

	return ptr;
}

void string_split (const char *string, char *left, char *right, char token)
{
	int i = 0;
	char *token_pos = string_find ((char *)string, token);
	
	/* checks if token is not found*/
	if (token_pos == string)
		return;
	
	while ((string + i) != token_pos)
	{
		left[i] = string[i];
		++i;
	}
	
	left[i] = '\0';

	/* Note: This is not godd! */
	strncpy (right, token_pos + 1, 200);
}
