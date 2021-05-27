/*
 * game.c
 *
 * Grace Wang
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ********** function prototypes ********* */
static int isnewline(int c);
static int never(int c);
char* file_readLine(FILE* fp);
char* file_readUntil(FILE* fp, int (*stopfunc)(int c));
static void printIntro();
static void printChoice(int idx);
static void promptUser();



/* ********* main ********** */
int main()
{
    printIntro();

    int idx = 6;
    char* input = NULL;
    printChoice(idx);
    idx--;
    promptUser();
    while ((input = file_readLine(stdin)) != NULL) {
      fprintf(stdout, "\n");
      if (strcmp(input,"no") == 0) {
          fprintf(stdout, "Congratulations, you learned your lesson\n");
          return 0;
      } else if (idx == 0) {
          fprintf(stdout, "You are back in your hovel \nMoral of the story:\nbe grateful for what you have. Greediness doesn't get you anywhere.");
          return 0;
      } else if (strcmp(input,"yes") == 0) {
        printChoice(idx);
        idx--;
      } 
      promptUser();
    }
    return 1;
}

static void 
promptUser()
{
  fprintf(stdout, "(yes or no): ");
}
static void
printIntro()
{
    fprintf(stdout, "Intro: \n");
    fprintf(stdout, "A magical flounder is able to grant you anything you wish for\n");
    fprintf(stdout, "It already granted you your wish to turn your hovel into a cottage\n");

}

static void
printChoice(int idx)
{
    if (idx == 6) {
      fprintf(stdout, "Now that you have your cottage, do you want to ask the flounder for a castle?\n");
    } else if (idx == 5) {
      fprintf(stdout, "Now that you have your castle, do you want to be king?\n");
    } else if (idx == 4) {
      fprintf(stdout, "Now that you are king, do you want to be emperor?\n");
    } else if (idx == 3) {
      fprintf(stdout, "Now that you are emperor, do you you want to be pope?\n");
    } else if (idx == 2) {
      fprintf(stdout, "Now that you are pope, you can't become anything greater...do you want to continue?\n");
    } else if (idx == 1) {
      fprintf(stdout, "The only thing greater is God...do you want to be like God?\n");
    }
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