#include "shell.h"

char * getInput() {
  char input[100];

  //get cwd to print prompt terminal-style
  char cwd[PATH_MAX -1];
  getcwd(cwd, sizeof(cwd));
  printf("%s: ", cwd);

  //get input from stdin and remove newline
  fgets(input, sizeof(input), stdin);
  *(strchr(input, '\n')) = '\0';

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

//joins str but as char** for use in notRedir
char* join(char** strA) {
  char* strArr = (char*) malloc(100);
  printf("no\n");
  int max = numPtrElements(strA);
  printf("a\n");
  int i;
  for (i=0; i<max; i++) {
    printf("i: %d\n",i);
    strcat(strArr, strA[i]);
  }
  printf("joined: %s\n", strArr);
  return strArr;
}

int notRedir(char** cmd) {
  int i, j, out=0, in=0, outA = 0;
  char *input, *output;
  int max = numPtrElements(cmd);
  for (i=0; i<max; i++) {
    for (j=0; j<strlen(cmd[i]); j++) {
      if (cmd[i][j] == '>') { //changing stdout
	out=2;

	if (j==0) { // > is isolated
	  return notRedir(split(join(cmd)," "));
	}
	
	//printf("OUT\n");
	output = &cmd[i][j+1];
	cmd[i][j] = '\0';//replace > with null so it isolates command for exec

      } if (cmd[i][j] == '<') { //changing stdin
	in = 2;
	//printf("IN\n");
	input = &cmd[i][j+1];
	cmd[i][j] = '\0';//replace < with null so it isolates command for exec
      } if ((j++ < strlen(cmd[i])) && (cmd[i][j] == '>') && (cmd[i][j+1] == '>')) { //changing stdout by appending [NOT WORKING YET]
	outA = 2;
	printf("OUT2\n");
	output = &cmd[i][j +2];
	cmd[i][j] = '\0'; cmd[i][j+1] = '\0';//replace >> with null so it isolates command for exec
      }
    }
  } if (!(out || in)) { return 1; } //bool: redir is true : needs to be run

  //redirection!
  int fd;
  if (out) {
    //printf("output: %s\n", output);
    fd = open(output,O_WRONLY | O_TRUNC | O_CREAT, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
  } if (in) {
    //printf("input: %s\n", input);
    fd = open(input, O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);
  } if (outA) {
    fd = open(output,O_APPEND);
    dup2(fd, STDOUT_FILENO);
    close(fd);
  }
  execvp(cmd[0], cmd);
  exit(1);
  
  return 0; //bool: redir is false : execvp was already run
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
      if (notRedir(cmd)) { 
	execvp(cmd[0], cmd);
	exit(1);
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
