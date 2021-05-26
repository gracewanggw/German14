/*
 * game.c
 *
 * Grace Wang
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int isnewline(int c);
static int never(int c);
char* file_readLine(FILE* fp);
char* file_readUntil(FILE* fp, int (*stopfunc)(int c));

int main()
{
    int idx = 5;
    char* input = NULL;
    while ((input = file_readLine(stdin)) != NULL) {
        if (strcmp(input,"n") == 0) {
            fprintf(stdout, "Congratulations, you learned your lesson\n");
            return 0;
        } else if (idx == 0) {
            fprintf(stdout, "GAME OVER \n Moral of the story: ");
            return 0;
        }
        idx--;
    }
    return 1;
}

static int isnewline(int c) { return (c == '\n'); }
static int never(int c) { return (0); }

char* file_readLine(FILE* fp) { return file_readUntil(fp, isnewline); }

char* 
file_readUntil(FILE* fp, int (*stopfunc)(int c))
{
  if (stopfunc == NULL) {
    stopfunc = never;
  }

  // allocate buffer big enough for "typical" words/lines
  int len = 81;
  char* buf = malloc(len * sizeof(char));
  if (buf == NULL) {
    return NULL;
  }

  // Read characters from file until stop-character or EOF, 
  // expanding the buffer when needed to hold more.
  int pos;
  char c;
  for (pos = 0; (c = fgetc(fp)) != EOF && !(*stopfunc)(c); pos++) {
    // We need to save buf[pos+1] for the terminating null
    // and buf[len-1] is the last usable slot, 
    // so if pos+1 is past that slot, we need to grow the buffer.
    if (pos+1 > len-1) {
      char* newbuf = realloc(buf, ++len * sizeof(char));
      if (newbuf == NULL) {
        free(buf);
        return NULL;
      } else {
        buf = newbuf;
      }
    }
    buf[pos] = c;
  }

  if (pos == 0 && c == EOF) {
    // no characters were read and we reached EOF
    free(buf);
    return NULL;
  } else {
    // pos characters were read into buf[0]..buf[pos-1].
    buf[pos] = '\0'; // terminate string
    return buf;
  }
}