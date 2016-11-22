#include "shell.h"

char * getInput() {
  char input[100];
  char cwd[PATH_MAX -1];
  getcwd(cwd, sizeof(cwd));
  printf("%s: ", cwd);
  fgets(input, sizeof(input), stdin);
  return input;
}

void cd(char * path);

void exit();

char ** split(char * str, char * delim) {
}

int main(int argc, char * argv[]) {
  printf("\nInput: %s",getInput());
}
