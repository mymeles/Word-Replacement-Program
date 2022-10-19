/**
 * @file line.h
 * @author Meles Meles
 * 
 * line.h is a header file for line.c. It holds the function
 * prototypes for readLine() and measureLine().
 */
#include <stdio.h>
#include <stdlib.h>

/**
 * This function counts and returns the number of characters in the next 
 * line of input from the given file. If there’s no more input, this function 
 * will return zero
 * 
 * @param fp which is a pointer to a file that is read
 * @return int count of characters in the next line else return zero for no more input.
 */
int measureLine( FILE *fp );

/**
 * This function will read the next input line from fp, storing it in str.
 * 
 * @param fp is the file stream read from
 * @param str is the array the characters are stored
 */
void readLine( FILE *fp, char str[] );
