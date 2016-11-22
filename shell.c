#include "shell.h"

char * getInput() {
  char input[100];
  char cwd[PATH_MAX -1];
  getcwd(cwd, sizeof(cwd));
  printf("%s: ", cwd);
  fgets(input, sizeof(input), stdin);
  *(strchr(input, '\n')) = NULL;
  char* retInput = (char*) malloc(sizeof(input));
  retInput = &input[0];
  return retInput;
}

void cd(char * path);

void exit();

char ** split(char * str, char * delim) {
  char *command[100];
  int i = 0;
  while((command[i] = strsep(&str, delim)))
    i++;
  //return command;
  char** cmd = (char**) malloc(sizeof(command));
  cmd = &command[0];
  return cmd;
}

int main(int argc, char * argv[]) {
  char *in = getInput();
  printf("\nInput: %s\n",in);
  char **in2 = split(in, " ");
  while(*in2) {
    printf("\nInput after split: %s",*in2);
    in2 ++;
  }
  printf("\n");
}
