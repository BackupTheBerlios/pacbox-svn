#include "string.h"

#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

#include "linked_list.h"

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

int	string_find_ch (char *str, char ch)
{
	int i;
	int str_len = strlen (str);
	
	if (strlen (str) == 0)
		return 0;
	
	for (i = 0; i < str_len; ++i)
	{
		if (ch == str[i])
			return 1;	
	}

	return 0;
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

LinkedList* string_split_tokens (char *str, char *tokens)
{
	ListNode *node;
	LinkedList *list = malloc (sizeof (LinkedList));
	int i;
	int counter = 0;
	int found = 0;
	char *current_pos = str;
	int str_len = strlen (str);

	list_init (list);
	
	for (i = 0; i < str_len; ++i)
	{
		if (string_find_ch (tokens, str[i]))
		{
			char *tmp;
			node = malloc (sizeof (ListNode));
			
			tmp = malloc ((counter + 1) * sizeof (char));
			strncpy (tmp, current_pos, (counter));
			tmp[counter] = '\0';
			
			node->data = tmp;

			list_add_node (list, node);
			
			current_pos = (str + (i + 1));
			found = 1;
			counter = 0;
		}
		
		counter++;
	}
	
	node = malloc (sizeof (ListNode));
		
	node->data = malloc ((counter + 1) * sizeof (char));
	strncpy ((char*)node->data, current_pos, counter);
			
	list_add_node (list, node);

	if (found)
		return list;
	else
	{
		list_clear (list);
		free (list);
		return 0;
	}
	
}
