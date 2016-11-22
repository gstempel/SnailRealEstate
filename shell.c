#include "shell.h"

char ** getInput();

void cd(char * path);

void exit();

char ** split(char * str, char * delim) {
  char **retVal = (char **) malloc(sizeof(str) * sizeof(char *));
  int i = 0;
  printf("%s",retVal[1]);
  while (str) {
    retVal[i] = strsep(&str, " ");
    i++;
  }
  retVal[i] = 0;
  printf("HELLO");
  return retVal;
}

int main(int argc, char * argv[]) {
  split("Emma B Vukelj", " ");
  return 0;
}
