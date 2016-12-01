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

char ** split(char * str, char * delim) {
  //effectively split str by delim
  char **command = (char**)malloc(100);
  int i = 0;
  while((command[i] = strsep(&str, delim)))
    i++;
  command[i] = 0;
  
  return command;
}

int numPtrElements(char** ptr) {
  int numChars = 0;
  while (*ptr++) {
    numChars++;
  }
  return numChars;
}

//joins str but as char** for use in notRedir
char* join(char** strA) {
  char* strArr = (char*) malloc(100);
  int max = numPtrElements(strA);
  int i;
  // keep appending each element to retVal
  for (i=0; i<max; i++) {
    strcat(strArr, strA[i]);
  }
  return strArr;
}

void piping(char* args, char* cmd) {
  //parse string
  char** newArgs = split(args,"|");
  int i, max = numPtrElements(newArgs);
  char** cmdsOut;
  for (i=0; i<max; i++) {
    printf("arg %d: %s\n", i, newArgs[i]);
  }
  
  //create helper file
  char *tmp = "pipeHelp"; //rename to hidden later
  int foo = open(tmp, O_CREAT | O_TRUNC | O_WRONLY, 0600);
  
  //redir strdout to foo
  int STDOUT_FILENO_DUP = dup(STDOUT_FILENO);
  dup2(foo, STDOUT_FILENO);
  printf("hello\n");
  //send initial command output to helper file
  char** toRun = split(newArgs[0]," ");
  toRun[numPtrElements(toRun)] = 0;
  int par = fork();
  if (par) {
    int status;
    wait(&status);
  } else {
    execvp(toRun[0], toRun);
  }
  close(foo);
  foo = open(tmp,O_RDONLY, 0600);
  
  //redir foo to stdin
  int STDIN_FILENO_DUP = dup(STDIN_FILENO);
  dup2(foo, STDIN_FILENO);
  dup2(STDOUT_FILENO_DUP, STDOUT_FILENO);
  
  //send second command (but foo as input!)
  char** secondRun = split(newArgs[1]," ");
  secondRun[numPtrElements(toRun)] = 0;

  int par2 = fork();
  if (par2) {
    int status;
    wait(&status);
  } else {
    execvp(secondRun[0], secondRun);
  }
  
  //put files back :)
  dup2(STDIN_FILENO_DUP, STDIN_FILENO);
}

int notRedir(char** cmd) {
  int i, j, out=0, in=0, outA = 0, inOut = 0;
  char *input, *output;
  int max = numPtrElements(cmd);
  for (i=0; i<max; i++) {
    for (j=0; j<strlen(cmd[i]); j++) {
      //Redirects stdout to a file by appending
      if (((j+1) <= strlen(cmd[i])) && (cmd[i][j] == '>') && (cmd[i][j+1] == '>')) {
	outA = 2;
	//change str format if >> is in weird place
	if (j==0 || j+1==strlen(cmd[i])-1) { return notRedir(split(join(cmd)," ")); }
	output = &cmd[i][j +2];
	cmd[i][j] = '\0';
	cmd[i][j+1] = '\0';//replace >> with null so it isolates command for exec

      }
      //Redirects stdout to a file
      else if (cmd[i][j] == '>' && (!(outA))) {
	out=2;
	//> is in weird place
	if (j==0 || j==strlen(cmd[i])-1) {
	  return notRedir(split(join(cmd)," "));
	}
	output = &cmd[i][j+1];
	cmd[i][j] = '\0';//replace > with null so it isolates command for exec
      }
      //Redirects stdin from a file
      else if (cmd[i][j] == '<') {
	in = 2;
	// < is in weird place
	if (j==0 || j==strlen(cmd[i])-1) {
	  return notRedir(split(join(cmd)," "));
	}
	input = &cmd[i][j+1];
	cmd[i][j] = '\0';//replace < w/ null so it isolates command for exec
      }
      //Redirect stdout from one command to stdin of the next
      else if (cmd[i][j] == '|') {
	inOut = 2;
	piping(join(cmd), input);
      }
    }
  }

  if (!(out || in || outA || inOut)) {  //bool: notRedir is true 
    return 1;
  }
  
  //redirection!
  int fd;
  if (outA) {
    //printf("output: %s\n", output);
    fd = open(output,O_APPEND | O_WRONLY, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
  } if (out) {
    //printf("output: %s\n", output);
    fd = open(output,O_WRONLY | O_TRUNC | O_CREAT, 0644);
    dup2(fd, STDOUT_FILENO);
    close(fd);
  } if (in) {
    //printf("input: %s\n", input);
    fd = open(input, O_RDONLY);
    dup2(fd, STDIN_FILENO);
    close(fd);
  } if (inOut) {
    return 0; //piping will be run in piping()
  }
  execvp(cmd[0], cmd);
  exit(1);
  
  return 0; //bool: notRedir is false. we redirected
}


void cd(char* path) {
  //needs separate fxn for possible error handling
  chdir(path);
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
