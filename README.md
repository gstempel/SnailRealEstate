# SnailRealEstate
by Grace Stempel, Emma Vukelj, Quinn Dibble

Features:
	 - Forks and executes commands
	 - Handles multiple commands entered at once (;)
	 - Redirects stdin or stdout (once per command)

Attempted:

Bugs:

Files & Function Headers:
shell.c: Handles shell operations

	/*======== char* getInput() ==========
	Returns: input entered by user through command line
	without a trailing newline

	Uses fgets to get input and strchr to handle the newline
	====================*/
	
	/*======== char** split(char * str, char * delim) ==========
	Inputs: string to be split by delimeter
	Returns: Array of strings, the result of splitting str by
	the given delimeter

	Uses strsep() to continuously parse str by delim until
	str is null
	====================*/

	/*======== int numPtrElements(char** ptr) ==========
	Inputs: pointer to be measured
	Returns: Number of elements in pointer
	====================*/

	/*======== char* join(char** strA) ==========
	Inputs: array of strings to be turned into one string
	Returns: one string, with strings of strA appended in order
	====================*/

	/*======== int notRedir(char** cmd) ==========
	Inputs: command (array of strings) to be checked for redirection
	Returns: int (boolean): 1 if no redirection, 0 if redirection
	====================*/

	/*======== void cd (char* path) ==========
	Inputs: relative or abs path user requests to cd into

	Uses chdir() to change current cwd of process to path
	====================*/

	/*======== void exec(char** cmd) ==========
	Inputs: arr of command line args to be executed

	Executes given command, checking for special cases (cd, exit)
	====================*/

	/*======== void run() ==========
	Infinite loop that gets, splits, and executes input
	====================*/