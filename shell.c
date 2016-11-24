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
      wait(0);
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
  run();
  return 0;
}
