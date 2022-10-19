/**
 * @file replace.c
 * @author Meles Meles(mymeles)
 * Replace.c is a program which finds and replaces selected words 
 * in an input text file as directed by the command line arguments.
 */
#include "line.h"
#include "expand.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/** Number of required arguments at the end of the command line. */
#define REQUIRED_ARGS 2

/**
 * main is the start of the program. With help from the other
 * components, it replaces target strings with their replacements 
 * in the input file and writes out the resulting text to the output.
 * If a command line argument strucure is invalid, if the files specified 
 * can not be opened, or if a word replacement is illegal, or if there is a 
 * duplicate target word it will exit out the program with a status of 1. 
 * @param argc is the an int type indicating the size of argv
 * @param argv is an array of char pointers to command line 0arguments. 
 * @return int the exit status of the program which is 0. 
 */
int main(int argc, char *argv[])
{
  if (argc % 2  == 0) {
    fprintf(stderr, "usage: replace (<target> <replacement>)* <input-file> <output-file>\n");
    exit(EXIT_FAILURE);
  }
  int lenWordList = argc - 3;               
  char *input = argv[argc - REQUIRED_ARGS]; 
  char *output = argv[argc - 1];            
  int t_r_list_len = lenWordList / 2;
  char *tlist[t_r_list_len]; 
  char *rlist[t_r_list_len]; 
  int tlistcount = 0;        
  int rlistcount = 0;        
  int maxRep = 0;
  if (lenWordList > 0) {
    for (int i = 1; i < argc - 1; i++) {
      if (i % 2 == 0) {
        int word_len = strlen(argv[i]);
        for (int j = 0; j < word_len; j++) {
          if (!wordChar(argv[i][j])) {
            fprintf(stderr, "Invalid word: %s\n", argv[i]);
            exit(EXIT_FAILURE);
          }
        }
        if (maxRep < strlen(argv[i])) {
          maxRep = strlen(argv[i]);
        }
        rlist[rlistcount++] = argv[i];
      }
      else {
        tlist[tlistcount++] = argv[i];
      }
    }
  }

  FILE *read = fopen(input, "r");   // opening file to read from
  FILE *write = fopen(output, "w"); // opening file to write to
  if (read == NULL || write == NULL) {
    fprintf(stderr, "Can't open file: %s\n", read == NULL ? input : output);
    exit(EXIT_FAILURE);
  }

  if (lenWordList > 0) {
    for (int i = 0; i < t_r_list_len; i++) {
      for (int j = i+1; j < t_r_list_len; j++){
        if (strcmp(tlist[j], tlist[i]) == 0) {
          fprintf(stderr, "Duplicate target: %s\n", tlist[j]);
          exit(EXIT_FAILURE);
        }
      }
    }
  }
  int measuredLined = measureLine(read);
  while(measuredLined) {
    char str[measuredLined + 1];
    readLine(read, str);
    int expandline = expansionBound(str, maxRep);
    char replacedLine[expandline + 1];
    expand(str, replacedLine, tlist, rlist, t_r_list_len);
    fprintf(write, "%s", replacedLine);
    measuredLined = measureLine(read);
  }
  fclose(read);
  fclose(write);
  return EXIT_SUCCESS;
}
