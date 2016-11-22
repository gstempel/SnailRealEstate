#include "shell.h"

char ** split(char * str, char * delim);

char ** getInput();

void cd(char * path);

void exit();

char ** split(char * str, char * delim) {
  char **retVal = (char **) malloc(sizeof(str) * sizeof(char *));
  int i = 0;
  while (str) {
    retVal[i] = strsep(&str, " ");
    i++;
  }
  retVal[i] = 0;
  printf("HELLO");
  return retVal;
}

int main(int argc, char * argv[]) {
  split("Emma Vukelj B", " ");
  return 0;
}
