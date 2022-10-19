/**
 * @file expand.h
 * @author Meles Meles(mymeles)
 * expand.h is a header file component which holds 
 * the function prototypes for header.c.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * This function returns true if the given character is a word character 
 * (a letter, a decimal digit or an underscore).
 * @param ch is a character type
 * @return true if the given character is a word character else returns false
 */
bool wordChar( int ch );

/**
 * expansionBound is a function which computes an upper bound on how long the given string, 
 * src, will be after all the target words are replaced by replacement strings.
 * @param src is a pointer of char to the source string
 * @param maxRep is a type int which holds the maximum lenght of a replacing word 
 * @return int which is the expanded bound lenght of the source string
 */
int expansionBound( char *src, int maxRep );

/**
 * This function creates a copy of the source string, src, in dest, but 
 * with every occurrence of a target string replaced by its replacement.
 * @param src is a pointer of char to the source string.
 * @param dest is a pointer of char to the destination string.
 * @param tList an array of pointers holding list of target strings given on the command line 
 * @param rList an array of pointers holding list of corresponding replacement strings given on the command line.
 * @param pairs is the size tList and rList array 
 */
void expand( char *src, char *dest, char *tList[], char *rList[], int pairs );
