#include "shell.h"

char * getInput() {
  char input[100];

  //get cwd to print prompt terminal-style
  char cwd[PATH_MAX -1];
  getcwd(cwd, sizeof(cwd));
  printf("%s: ", cwd);

  //get input from stdin and remove newline
  fgets(input, sizeof(input), stdin);
  *(strchr(input, '\n')) = NULL;

  //turn stack mem to persistent mem for return
  char* retInput = (char*) malloc(sizeof(input));
  retInput = &(input[0]);
  return retInput;
}

void cd(char* path) {
  //needs separate fxn for possible error handling
  chdir(path);
}

char ** split(char * str, char * delim) {
  //effectively split str by delim
  char *command[100];
  char* copy = str;
  int i = 0;
  while((command[i] = strsep(&copy, delim)))
    i++;
  command[i] = 0;
  
  //turn heap mem to more persistent mem for return
  char** cmd = (char**) malloc(sizeof(char*) * 100);
  //IS ISSUE HERE
  return cmd;
}

void exec(char** cmd) {
  //handle special cases where forking is wrong approach
  if (!(strcmp(cmd[0],"exit"))) {
    exit(0);
  } else if (!(strcmp(cmd[0], "cd"))) {
    cd(cmd[1]);
  } else { //no special case
    int parent = fork();
    if (parent) {
      int status;
      wait(&status); //wait for child
    } else { //this is child
      execvp(cmd[0], cmd);
    }
  }
}

int numPtrElements(char** ptr) {
  int numChars = 0;
  while (*ptr++) {
    numChars++;
  }
  return numChars;
}

void run() {
  while (1) {
    char** cmds = split(getInput(),";");
    int i;
    int max = numPtrElements(cmds);
    for (i=0; i<max; i++) {
      char* cmd = (char*) malloc(strlen(cmds[i]) + 1);
      strcpy(cmd, cmds[i]);

      //WHY IS SPLIT AFFECTING ORIGINAL CMDS??
      printf("BEFORE: %s\n", cmds[i]);
      char** cmdSplit = split(cmd," ");
      printf("AFTER: %s\n", cmds[i]);

      free(cmdSplit);
      free(cmd);
      //exec(cmdSplit);
    }
  }
}

int main(int argc, char * argv[]) {
  run();
  return 0;
}
