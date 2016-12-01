#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

//split str by delim
char ** split(char * str, char * delim);

//return number of char*'s in ptr
int numPtrElements(char** ptr);

//return string with all strings in strA appended in order
char* join(char** strA);

//handle piping picked up in notRedir
void piping(char** args, char* cmd);

//return 1 if no redir/piping in cmd, else return 1
int notRedir(char** cmd);

//return userInput for command without \n
char * getInput();

//change current directory
void cd(char * path);

//check for special cases and execute single command
void exec(char** cmd);

//handle and execute received input
void run();
