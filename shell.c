#include "shell.h"

char ** getInput();

void cd(char * path);

void exit();

char ** split(char * str, char * delim) {
  char **retVal = (char **)malloc(sizeof(str) * sizeof(char *));
  int i = 0;
  while (str) {
    retVal[i] = strsep(&str, delim);
    i++;
  }
  retVal[i] = 0;
  return retVal;
}

int main(int argc, char * argv[]) {
  printf("val: %s\n",split("Emma B Vukelj", " ")[0]);
  return 0;
}
