#include "string.h"

#include <string.h>
#include <ctype.h>


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
	
	/* checks if token is not found */
	if (token_pos == string)
		return;
	
	while ((string + i) != token_pos)
	{
		left[i] = string[i];
		++i;
	}
	
	left[i] = '\0';

	/* Note: This is not godd! */
	strncpy (right, token_pos + 1, 500);
}


void string_trim (char *string)
{	
	int i = 0;
	int j = 0;
	int pos = 0;

	/* how many spaces to the left? */
    for (i=0; i<strlen(string); i++)
	{
        if ((!isspace(string[i])) && (string[i] != '\t'))
            break;
    }

	/* how many spaces to the right? */
    for (j=strlen(string)-1; j>=0; j--)
	{
        if ((!isspace(string[j])) && (string[j] != '\t') && (string[j] != '\n'))
            break;
    }

    /* move string to begin at position 0 */
    for (pos=i; pos<=j; pos++)
	{
        string[pos-i] = string[pos];
    }
    string[j+1-i] = '\0';
}
