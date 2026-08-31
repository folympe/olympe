*This project has been created as part of the 42 curriculum by olfhal*

## MINISHELL

## Description

## Instructions

update_wds:
*	Updates the PWD and OLDPWD in the environment after a directory change.
*	A copy of the paths are stored internally for use in case the environment
*	variables are unset.

chdir_errno_mod:
*	chdir can sometimes set errno to ESTALE ("Stale file handle")
*	when a parent directory is removed on some systems. This is due
*	to the inode table entry being recycled. This is a fix to display
*	"no such file or directory" error instead.

change_dir:
*	Changes the current working directory and updates the
*	OLDPWD environment variable.
*	Returns 1 on success, 0 on failure.

cd_builtin:
*	Executes the builtin cd command by changing the working directory.
*	Returns 0 on success, 1 on failure.

**

is_n_flag:
*	Checks whether an arg is an -n option flag.
*	Returns true if the arg is some variation of -n, -nnnn, -nn, etc.
*	Returns false if it contains anything other than - and n (ex. --n -nnnm -n1234)

echo_print_args:
*	Prints the given array of aruments to STDOUT.

echo_builtin:
*	Executes the echo builtin command: prints the given strings
*	and adds a \n character or not depending on the -n option.
*	Returns 1 on completion.

**

env_builtin:
*	Executes the builtin env command: Prints the environment variables.

**

check_out_of_range:
*	Checks if the number goes over LONG_MAX or LONG_MIN.
*	Sets an error boolean to true if the number is out of range, false if not.

ft_atoi_long:
*	Transforms a string comprised of digits into a long integer.
*	Returns the long integer. In case of error, sets an error boolean
*	to true.

get_exit_code:
*	Gets the exit code from the arguments given to the exit builtin.
*	Returns 0 if no arguments were provided.
*	Returns 2 in case argument is not digits.
*	Returns the numeric exit code on success.

is_quiet_mode:
*	If exit is not called alone, it should not print "exit".
*	Returns true if exit should not be printed. False if exit was called
*	alone and the "exit" message should be printed.

exit_builtin:
*	Executes the exit builtin.
*	If alone, prints exit and exits the shell with the provided exit code, or 0.
*	If piped, exits the child process with the provided exit code and does not exit
*	minishell.
*	In case of failure due to invalid arguments, does not exit the shell
*	and returns an error exit code (1 or 2) instead.

**

get_key_value_pair:
*	Separates the given argument into a key-value pair
*	for the environment variable.
*	Returns an array of 2 strings containing the key and the
*	value of the new environment variable.
*	Returns NULL in case of error.

export_builtin:
*	Adds the given variables to the environment variables.
*	Returns 0 if all args were successfully added to env,
*	or 1 if one or more args were not added to env.

**

pwd_builtin:
*	Executes the builtin pwd command and displays the
*	current working directory path.
*	Returns 0 if successful, 1 if an error occured.

**

unset_builtin:
*	Removes the environment variables with the given keys
*	after checking if they are valid keys.
*	Does nothing if the key is not in the environment.
*	Returns 0 if all args were successfully unset, or 1 if
*	one or more args could not be unset.

**

realloc_env_vars:
*	Reallocates memory for the global variable g_env_vars.
*	Returns a pointer to the new environment variables
*	or NULL in case of a memory allocation error.


set_env_var:
*	Adds an environment variable with the given key
*	corresponding to the given value. If the key already
*	exists in the environment variables, the value will
*	be overwritten. If not, it creates a new entry.
*	Returns 1 if the operation was successful, or 0 if
*	in case of error.

remove_env_var:
*	Removes the variable at the given index from the
*	environment variables.
*	Returns 1 if the removal was successful, 0 if case
*	of an invalid index or a memory allocation error.

**

env_var_count:
*	Counts how many original environment variables there are.
*	Returns the number of environment variables.

get_env_var_index:
*	Searches for the given variable in the environment variables.
*	Returns the index of the variable in the environment
*	matching the given string. Partial variable names are not
*	supported: the given string must be a full variable name.
*	Returns -1 if the string cannot be found in the environment.

get_env_var_value:
*	Searches for the given variable in the environment variables.
*	Returns a pointer to the value of the variable in the environment
*	matching the given string. Partial variable names are not
*	supported: the given string must be a full variable name.
*	Returns NULL if the string cannot be found in the environment.

is_valid_env_var_key:
*	Checks if the key is a valid name for an evironment
*	variable.
*	Returns true if the key contains only alphanumeric chars
*	or '_', or false if not.

**

execute_builtin:
*	Executes the given command if it is a builtin command.
*	Returns -1 if the command is not a builtin command.
*	Returns 0 or 1 if the builtin command succeeded or failed.

execute_sys_bin:
*	Executes the command's system binary file if it can be found
*	among the environment executable paths.
*	Returns CMD_NOT_FOUND if a path to the executable bin file cannot be
*	found. Returns 1 in case of failure to run existing, executable
*	file.

execute_local_bin:
*	Attempts to execute the given command as is, in case
*	it is a local directory file or already contains the
*	path to bin.
*	Returns CMD_NOT_FOUND if the command is not an existing executable
*	file. Returns 1 in case of failure to launch executable.

execute_command:
*	Child process tries to execute the given command by setting
*	its input/output fds and searching for an executable.
*	Searching for executable in this order:
*		1. Execute builtin command
*		2. Execute system binaries for command.
*		3. Execute given command name directly (local bin)
*	If it cannot find a matching builtin or executable,
*	prints an error message.
*	Child exits with it's executed program's exit code, or 1 if
*	it could not find one.

**

cmd_is_dir:
*	Checks if the command is a directory rather than an executable.
*	Returns true if the command is a directory, false if not.

check_command_not_found:
*	Searches for the reason a command was not found in the system binaries.
*	Returns an error message and status if the command is invalid,
*	returns EXIT_SUCCESS if the command is valid and should be executed
*	as a local executable.

**

get_children:
*	Waits for children to terminate after cleaning up fds and the command
*	list.
*	Returns a child's exit status as bash does:
*		"The return status (see Exit Status) of a simple command is its
*		exit status as provided by the POSIX 1003.1 waitpid function, or
*		128+n if the command was terminated by signal n."
*	If there are multiple commands in a pipeline:
*		"The exit status of a pipeline is the exit status of the last command
*		in the pipeline"

create_children:
*	Creates a child process for each command to execute, except in the
*	case of a builtin command that is not piped, which executes in the
*	main process (no children created in this case).
*	Returns true when a process was created for each command or when a
*	builtin was executed alone.
*	Returns false if there was a fork error.

prep_for_exec:
*	Prepares the command list for execution, creates pipes
*	and checks the input and output files.
*	Returns false in case of error, true if all is ready to
*	execute.

execute:
*	Executes the given commands by creating children processes
*	and waiting for them to terminate.
*	Returns the exit code of the last child to terminate. Or
*	exit code 1 in case of failure in the child creation process.

**

find_valid_cmd_path:
*	Checks access and permissions for each possible command path to find
*	a valid path to binay files for a command.
*	Returns the valid path to a command binary, or NULL if no valid path is
*	found.

get_paths_from_env:
*	Attempts to extract paths from the PATH environment variable.
*	Returns an array of paths on success. On failure, returns NULL.

get_cmd_path:
*	Searches the PATH environment variable for the location of the given
*	command's binary file.
*	Returns the path to the command binary file. NULL if no valid path
*	is found.

**

restore_io:
*	Restores the original standard input and standard output
*	to their original fds of 0 and 1. Used to clear the input/output
*	fds after execution, in preparation for the next set of user commands.
*	Returns 1 if the duplication was successful, 0 if not.

redirect_io:
*	Duplicates the input and output fds to the standard input and output.
*	Backs up the standard input and output before replacing them in order
*	to restore them after execution.
*	Returns 1 for success, 0 in case of error.

check_infile_outfile:
*	Checks if the infile and outfile are set correctly.
*	Returns 1 on success, 0 on failure.

**

close_pipe_fds:
*	Closes the pipe fds of all commands. A pointer to a command to skip
*	can be specified to skip closing that command's pipe fds:
*		- The parent will specify NULL for the skip command while closing
*		all pipe fds.
*		- The child will specify its own command as skip command while
*		closing all pipe fds so as to not accidentally close its own
*		pipe fds.

create_pipes:
*	Creates a set of pipes for each piped command in the list
*	of commands.
*	Returns 1 if successful, 0 in case of failure.

set_pipe_fds:
*	Sets the pipe fds for this command. If the previous command
*	was piped to this one, sets the input as the read end of
*	the previous command. If this command is piped to the
*	next, sets the output ad the write end of the pipe.
*		pipe_fd[0] = read end of pipe.
*		pipe_fd[1] = write end of pipe.
*	Returns true when the pipe file descriptors are set.

**

free_data:
*	Frees all of the data used to run a command. If clear_history is true,
*	frees the environment and the command history before returning.

close_fds:
*	Closes opened file descriptors, including pipes and input and
*	output fds. If close_backups is set to true, it also closes
*	backup STDIN and STDOUT file descriptors.

free_io:
*	Frees the input/output fd structure.

free_str_tab:
*	Frees an array of strings.

free_ptr:
*	Frees a pointer of any type if it is not NULL and sets it to NULL.
*	This avoids accidental double-frees.

**

join_strs:
*	Joins two strings together, freeing the previous string.
*	Returns the new concatenated string. Or NULL if an error occured.

add_detail_quotes:
*	Checks whether to add quotes around the error detail:
*	i.e. "unset: `@': not a valid identifier"
*	Returns true if the command is export or unset,
*	false if not.

errmsg_cmd:
*	Prints an error message to the standard error, prefixed with the
*	program name.
*	Returns with the specified error number.

errmsg:
*	Prints an error message that is unrelated to a specific command.
*	Used in parsing phase for syntax errors.

usage_message:
*	Prints a usage message. Used if start-up arguments are invalid.

**
# minishell
exit_shell:
*	Cleanly exits the minishell program by closing all opened
*	fds and freeing all allocated memory.

**
# minishell
init_env:
*	Initializes a data variable with the contents of the environment
*	variables inherited from the original shell.
*	Returns 0 on failure, 1 on success.

init_wds:
*	Initializes working directory variables as a safeguard against
*	environment PWD and OLDPWD being unset or otherwise not present
*	in the environment. Used for cd builtin.
*	Returns true if successful, false in case of error.

/* init_data:
*	Initializes the data structure used in parsing and executing user input.
*	Returns true if successful, false in case of error.

/* init_io:
*	Initializes a structure with default values to contain
*	infile and outfile information for a command.

### Resources
les studes de 42
l'ia m'a aider avec les normes 