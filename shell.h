#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <limits.h>

char ** split(char * str, char * delim);

char * getInput();

void cd(char * path);

void exit();

void run();

void exec(char** cmd);
