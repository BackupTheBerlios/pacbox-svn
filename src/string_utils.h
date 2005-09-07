#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

typedef struct {
	char *list[50];
	int num_items;
} StringList;

/*
 * If not found the pointer to the first character
 * is returned
 */
char * string_find (char *str, char ch);

/* Checks if a char is in the string */
int	string_find_ch (char *str, char ch);

/* Splits a string between the given token, 
 * and put the left in left argument
 * and right in the right argument */
void string_split (const char *string, char *left, char *right, char token);

/* Trims whitespace from both edges of a string
 * WARNING: Modifies existing string */
void string_trim (char *string);

/* Takes a string and splits it based on the tokens.
 * Puts all the string in the list argument
 * and puts the legnth of the string array
 * in the length argument.
 * Returns 1 if any tokens found, else 0 */
int string_split_tokens (char *str, 
						 char *tokens, 
						 char **list, 
						 int *length);

#endif /* _STRING_UTILS_H_ */
