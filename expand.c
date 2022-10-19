/**
 * @file expand.c
 * @author Meles Meles(mymeles)
 * This component takes care of replacing occurrences of the 
 * target words with their replacement strings in a line of text.
 */
#include "expand.h"
#include <string.h>

bool wordChar(int ch)
{
   if (ch >= 'A' && ch <= 'Z') {
      return true;
   }
   else if (ch >= 'a' && ch <= 'z') {
      return true;
   }
   else if (ch == '_' || (ch >= '0' && ch <= '9')) {
      return true;
   }
   return false;
}

int expansionBound(char *src, int maxRep)
{
   int expandedcount = 0;
   int tempcount = 0;
   int idx = strlen(src);
   for (int i = 0; i < idx; i++) {
      if (!wordChar(src[i])) { 
         tempcount = 0;
         int j = 0;
         for (j = i; !wordChar(src[j]) && j < idx; j++) {
            tempcount++;
         }
         i = j;
         if (maxRep >= tempcount) {
            tempcount = maxRep;
         }
         expandedcount += tempcount;
         if (i >= idx) {
            break;
         }
      }
      expandedcount++;
   }
   return expandedcount;
}

/**
 * This function returns true if the given character is a word character
 * (a letter, a decimal digit or an underscore).
 * @param ch is a character type
 * @return true if the given character is a word character else returns false
 */

static bool check_word(char *src, char *word, int idx)
{
   int replaced_word_len = strlen(word);
   int counter = 0;
   bool isDuplicate = false;
   int i = idx;
   for (i = idx; i < idx + replaced_word_len; i++) {
      if (src[i] == word[counter++]) {
         isDuplicate = true;
      }
      else {
         return false;
         break;
      }
   }
   if (wordChar(src[i]) || wordChar(src[idx - 1]))
      isDuplicate = false;
   return isDuplicate;
}

/**
 * addtodestination() is a helper fuction that takes a replacing word 
 * as a pointer and adds it to the destination string at the specified index
 * @param dest a pointer to a char of the destination string 
 * @param word a pointer to a char to the replaced word written in destination string
 * @param idx location the word is written in destination string 
 * @return int the next location in the destination string a char is written in
 */
static int addtodestination(char *dest, char *word, int idx)
{
   int wordlen = 0;
   int word_len = strlen(word);
   int i = idx;
   for (i = idx; i < idx + word_len; i++)
      dest[i] = word[wordlen++];
   return i;
}

void expand(char *src, char *dest, char *tList[], char *rList[], int pairs)
{
   int src_length = strlen(src);
   int i, j;
   int dest_index = 0;
   for (i = 0; i < src_length; i++) {
      if (wordChar(src[i])) {
         for (j = 0; j < pairs; j++) { // the man 
            int word_lem = strlen(tList[j]);
            if ((src[i] == tList[j][0] ) && (src[i + word_lem -1] == tList[j][word_lem-1])) {
              // printf("%c %c %c %c\n", src[i],tList[j][0], src[i + word_lem -1],tList[j][word_lem-1]);
               if (check_word(src, tList[j], i)) {
                  dest_index = addtodestination(dest, rList[j], dest_index);
                  i = i + strlen(tList[j]);
                  break;
               }
            }
         }
      }
      dest[dest_index++] = src[i]; 
   }
   dest[dest_index] = '\0';
}
