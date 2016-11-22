#include "shell.h"

char * getInput() {
  char input[100];
  char cwd[PATH_MAX -1];
  getcwd(cwd, sizeof(cwd));
  printf("%s: ", cwd);
  fgets(input, sizeof(input), stdin);
  *(strchr(input, '\n')) = NULL;
  return input;
}

void cd(char * path);

void exit();

char ** split(char * str, char * delim) {
  str[strlen(str) - 1] = 0;
  char *command[100];
  int i = 0;
  while(str) {
    command[i] = strsep(&str, delim);
    i++;
  }
  command[i] = 0;
  return command;
}

int main(int argc, char * argv[]) {
  char *in = getInput();
  printf("\nInput: %s",in);
  char **in2 = split(in, " ");
  while(*in2) {
    printf("\nInput after split: %s",*in2);
    in2 ++;
  }
  printf("\n");
}
