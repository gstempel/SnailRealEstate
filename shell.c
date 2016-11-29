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
  char* retInput = (char*) malloc(strlen(input)+1);
  strcpy(retInput, input);
  return retInput;
}

void cd(char* path) {
  //needs separate fxn for possible error handling
  chdir(path);
}

char ** split(char * str, char * delim) {
  //effectively split str by delim
  char **command = (char**)malloc(100);
  int i = 0;
  while((command[i] = strsep(&str, delim)))
    i++;
  command[i] = 0;
  
  //turn heap mem to more persistent mem for return

  return command;
}

int redir(char** cmd) {
  int i, j, out=0, in=0;
  for (i=0; i<numPtrElements(cmd); i++) {
    for (j=0; j<strlen(cmd[i]); j++) {
      if (cmd[i][j] == '>') {
	out = 1; //we are changing stdout
      } if (cmd[i][j] == '<') {
	in = 1;
      }
    }
  } if (!(out) && !(in)) { return 0; }
  printf("Redirection! To do\n");
  return 1;
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
      if (!(redir(cmd))) { 
	execvp(cmd[0], cmd);
      }
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
    char* thing = getInput();
    char** cmds = split(thing,";"); //split sep commands
    int i;
    int max = numPtrElements(cmds);
    for (i=0; i<max; i++) { //run each command
      char* cmd = (char*) malloc(strlen(cmds[i]) + 1);
      strcpy(cmd, cmds[i]);
      char** cmdSplit = split(cmd," ");

      exec(cmdSplit);
      free(cmd);
    }
  }
}

int main(int argc, char * argv[]) {
  run();
  return 0;
}
