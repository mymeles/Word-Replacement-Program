/**
 * @file line.c
 * @author Meles Meles(mymeles)
 *
 * This file which holds the functions readLine and
 * measure line is used to read files and also get the
 * lenght of a read line in a file if there is any.
 */
#include "line.h"
#include <stdio.h>
#include <stdlib.h>

int measureLine(FILE *fp)
{
  long currpos = ftell(fp);
  int lineLength = 0;
  char ch = fgetc(fp);
  while (ch != EOF) {
    lineLength++;
    if (ch == '\n') {
      break;
    }
    ch = fgetc(fp);
  }
  fseek(fp, currpos, SEEK_SET);
  return lineLength;
}

void readLine(FILE *fp, char str[])
{
  char ch = fgetc(fp);
  int idx = 0;
  while (ch != EOF) {
    str[idx++] = ch;
    if (ch == '\n') {
      break;
    }
    ch = fgetc(fp);
  }
  str[idx] = '\0';
}
