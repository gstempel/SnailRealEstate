#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

char ** split(char * str, char * delim);

char * getInput();

void cd(char * path);

void run();

void exec(char** cmd);

int numPtrElements(char** ptr);
