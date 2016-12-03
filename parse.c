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
  if (delim[0] == ' ') {
    int j;
    for (j=0; j<i; j++) {
      if (command[j][0] == 'l' && command[j][1] == 's') {
	strcpy(command[j],"ls");
      }
    }
  }
  
  return command;
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
