*This project has been created as part of the 42 curriculum by olfhal and by jiasmoun*

# Minishell

## Description

Minishell is a small Unix ahell written in C. The goal of the project is to understand how a shell reads, parses and executes commands while reproducing part of Bash behaviour.

The project handles command history, environment variables, expansions, auotes, pipes, redirections, heredocs and signals.
It also implements the required builtins : `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.

The main execution flow is:

`readline -> tokenizer -> AST -> command list -> execution`

## Instructions

Compile the project with :

```bash
make
```

Run Minishell with :

``bash
./minishell
```

Useful Makefile rules :

```bash

make clean
make fclean
make re
```

Once launched, commands can be entered directly in the prompt like in a regular shell.

## Resources

The main resources used during the project were the 42 Minishell subject, 42 course material and the documentation related to the system functions required by the project. 
The Bash manual to compare the behaviour of builtins, pipes redirections...
Linux man pages
GNU Readline documentation

## Additional section - AI usage

AI was used during the project as a technical support tool. We mainly used to check why some parts of the parsing or execution flow were not behaving as expected.
It also helped us to reformulate or simplify explanations while preparing for the project defense. 
Every change kept in the final project was reviewed, tested, and discussed within the team.
