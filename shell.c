#include "shell.h"

char * getInput() {
  char input[100];
  char cwd[PATH_MAX -1];
  getcwd(cwd, sizeof(cwd));
  printf("%s: ", cwd);
  fgets(input, sizeof(input), stdin);
  *(strchr(input, '\n')) = NULL;
  char* retInput = (char*) malloc(sizeof(input));
  retInput = &(input[0]);
  return retInput;
}

void cd(char* path) {
  chdir(path);
}

char ** split(char * str, char * delim) {
  char *command[100];
  int i = 0;
  while((command[i] = strsep(&str, delim)))
    i++;
  //return command;
  char** cmd = (char**) malloc(sizeof(command));
  cmd = &(command[0]);
  return cmd;
}

void exec(char** cmd) {
  if (!(strcmp(cmd[0],"exit"))) {
    exit(0);
  } else if (!(strcmp(cmd[0], "cd"))) {
    cd(cmd[1]);
  } else {
    int parent = fork();
    if (parent) {
      wait();
    } else {
      execvp(cmd[0], cmd);
    }
  }
}

void run() {
  while (1) {
    exec(split(getInput()," "));
  }
}

int main(int argc, char * argv[]) {
  /*char *in = getInput();
  printf("\nInput: %s\n",in);
  char** in2 = split(in, " ");
  char** saveIn2 = in2;
  while(*in2) {
    printf("\nInput after split: %s",*in2);
    in2 ++;
  }
  printf("\n");*/
  run();
  return 0;
}
