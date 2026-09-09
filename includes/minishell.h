/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 01:39:07 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 07:57:12 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <limits.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libft.h"
# include "tokenizer.h"
# include "ast.h"
# include "signals.h"


#define PROMPT "\001\e[40m\e[32m\002 Minishell>$ \001\e[0m\002"
# define HEREDOC_NAME "/tmp/.minishell_heredoc_"
# define CMD_NOT_FOUND 127
# define CMD_NOT_EXECUTABLE 126
# define SUCCESS 0
# define FAILURE 1

# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

typedef struct s_expand_token
{	
	char			*str;
	char			*str_backup;
	bool			var_exists;
	int				type;
	int				status;
	bool			join;
	struct s_expand_token	*prev;
	struct s_expand_token	*next;
}	t_expand_token;

typedef struct s_io_fds
{
	char	*infile;
	char	*outfile;
	char	*heredoc_delimiter;
	bool	heredoc_quotes;
	int		fd_in;
	int		fd_out;
	int		stdin_backup;
	int		stdout_backup;
}	t_io_fds;

typedef struct s_redir
{
	t_token_type		type;
	char			*word;
	char			*heredoc_file;
	struct s_redir		*next;
}	t_redir;

typedef struct s_command
{
	char				*command;
	char				*path;
	char				**args;
	bool				pipe_output;
	t_token_type			next_op;
	int				*pipe_fd;
	t_io_fds			*io_fds;
	t_redir				*redirs;
	bool				is_subshell;
	struct s_command        	*subshell;
	struct s_command		*next;
	struct s_command		*prev;
}	t_command;

typedef struct s_data
{
	bool			interactive;
	t_expand_token		*token;
	char			*user_input;
	char			**env;
	char			*working_dir;
	char			*old_working_dir;
	t_command		*cmd;
	pid_t			pid;
	int			last_exit_code;
}	t_data;

enum e_token_types 
{
	SPACES = 1,
	WORD,
	VAR,
	PIPE,
	INPUT,
	TRUNC,
	HEREDOC,
	APPEND,
	END
};

enum e_quoting_status
{
	DEFAULT,
	SQUOTE,
	DQUOTE
};

/* 	INIT */

bool		init_data(t_data *data, char **env);
void		init_io(t_command *cmd);

/* EXIT - ERROR */

void		exit_shell(t_data *data, int exno);
int		errmsg_cmd(char *command, char *detail, char *error_message, int error_nb);
void		errmsg(char *errmsg, char *detail, int quotes);
bool		usage_message(bool return_val);
char		*join_strs(char *str, char *add);

/* CLEAN_UP */

void		free_data(t_data *data, bool clear_history);
void		close_fds(t_command *cmds, bool close_backups);
void		free_io(t_io_fds *io);
void		free_ptr(void *ptr);
void		free_str_tab(char **tab);
void		free_token_list(t_token **tokens);
void		free_expand_token_list(t_expand_token **tokens);
void		lst_clear_cmd(t_command **cmds);

/* ENV */

int		env_var_count(char **env);
int		get_env_var_index(char **env, char *var);
char		*get_env_var_value(char **env, char *var);
bool		is_valid_env_var_key(char *var);
bool		set_env_var(t_data *data, char *key, char *value);
bool		remove_env_var(t_data *data, int idx);

/* BUILTINS */

int		env_builtin(t_data *data, char **args);
int             pwd_builtin(t_data *data, char **args);
int             echo_builtin(t_data *data, char **args);
int             export_builtin(t_data *data, char **args);
int             unset_builtin(t_data *data, char **args);
int             cd_builtin(t_data *data, char **args);
int             exit_builtin(t_data *data, char **args);

/* EXECUTION */

int		execute(t_data *data);
int             execute_pipeline(t_data *data);
int             execute_command(t_data *data, t_command *cmd);
int             execute_builtin(t_data *data, t_command *cmd);
bool		cmd_is_dir(char *cmd);
int		check_command_not_found(t_data *data, t_command *cmd);
char		*get_cmd_path(t_data *data, char *cmd);

/* PIPES - REDIRECTION */

bool		create_pipes(t_data *data);
bool		set_pipe_fds(t_command *cmds, t_command *curr_cmd);
void		close_pipe_fds(t_command *cmds, t_command *skip_cmd);
bool		check_infile_outfile(t_io_fds *io);
bool		redirect_io(t_io_fds *io);
bool		restore_io(t_io_fds *io);
bool		prepare_command_redirs(t_data *data, t_command *cmd);
bool            prepare_heredoc(t_data *data, t_io_fds *io, const char *delimiter);
bool		get_heredoc(t_data *data, t_io_fds *io);
bool		fill_heredoc(t_data *data, t_io_fds *io, int fd);

/* EXPANSION */

bool		is_var_compliant(char c);
int		var_length(char *str);
char		*identify_var(char *str);
int		count_len(char *str, int count, int i);
bool		quotes_in_string(char *str);
int		handle_quotes(t_data *data);
int		remove_quotes(t_expand_token **token_node);
char		*recover_val(t_expand_token *token, char *str, t_data *data);
int		replace_var(t_expand_token **token_node, char *var_value, int index);
char		*replace_str_heredoc(char *str, char *var_value, int index);
char		*var_expander_heredoc(t_data *data, char *str);
void		copy_var_value(char *new_str, char *var_value, int *j);
char		*get_new_token_string(char *oldstr, char *var_value, int newstr_size, int index);
int		expand_token_word(t_data *data, t_expand_token **cur);
char		*expand_word(t_data *data, const char *word);
bool		expand_command_group(t_data *data, t_command *cmd);

/* AST -> t_command */

bool	ast_to_commands(t_data *data, t_node *tree, t_command **commands);

/* DEBUG */

void	print_cmd_list(t_data *data);
void	print_expand_token_list(t_expand_token **tokens);

#endif
