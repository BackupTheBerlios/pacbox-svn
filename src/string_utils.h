#ifndef _STRING_H_
#define _STRING_H_

/* Returns the position of the given character 
 * If not found the pointer to the first character
 * is returned
 */
char * string_find (char *str, char ch);

/* Splits a string between the given token, and put the left in left argument
 * and right in the right argument
 */
void string_split (const char *string, char *left, char *right, char token);

#endif /* _STRING_H_ */
