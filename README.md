# SnailRealEstate
by Grace Stempel, Emma Vukelj, Quinn Dibble

Features:
	Forks and executes commands!

Attempted:

Bugs:

Files & Function Headers:
shell.c: Handles shell operations
	
	/*======== char** split(char * str, char * delim) ==========
	Inputs: string to be split by delimeter
	Returns: Array of strings, the result of splitting str by
	the given delimeter

	Uses strsep() to continuously parse str by delim until
	str is null
	====================*/

	/*======== char* getInput() ==========
	Returns: input entered by user through command line
	without a trailing newline

	Uses fgets to get input and strchr to handle the newline
	====================*/

	/*======== void cd (char* path) ==========
	Inputs: relative or abs path user requests to cd into

	Uses chdir() to change current cwd of process to path
	====================*/

	/*======== void run() ==========
	Infinite loop that gets, splits, and executes input
	====================*/

	/*======== void exec(char** cmd) ==========
	Inputs: arr of command line args to be executed

	Executes given command, checking for special cases (cd, exit)
	====================*/