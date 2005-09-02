#ifndef _STRING_UTILS_H_
#define _STRING_UTILS_H_

/* Returns the position of the given character 
 * If not found the pointer to the first character
 * is returned
 */
char * string_find (char *str, char ch);

/* Splits a string between the given token, and put the left in left argument
 * and right in the right argument
 */
void string_split (const char *string, char *left, char *right, char token);

/* Trims whitespace from both edges of a string
 * WARNING: Modifies existing string
 */
void string_trim (char *string);

#endif /* _STRING_UTILS_H_ */
