/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 03:09:38 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 08:16:31 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "ast_to_cmd.h"

static bool	line_is_blank(const char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space_to_skip(line[i]))
		i++;
	return (line[i] == '\0');
}

static void	set_syntax_error(t_data *data, t_ast_res res)
{
	char	*detail;

	detail = "newline";
	if (res.token)
		detail = (char *)get_token_name(res.token->type);
	errmsg("syntax error near unexpected token", detail, 1);
	data->last_exit_code = 2;
}

static void	run_line(t_data *data, char *line)
{
	t_token		*tokens;
	t_ast_res	res;

	if (line_is_blank(line))
		return ;
	add_history(line);
	tokens = tokenizer(line);
	if (!tokens)
	{
		data->last_exit_code = 2;
		return ;
	}
	res = ast_builder(tokens, TOKEN_NONE);
	if (!res.success)
		set_syntax_error(data, res);
	else if (ast_to_commands(data, res.tree, &data->cmd))
		data->last_exit_code = execute(data);
	else if (g_signal != SIGINT)
		data->last_exit_code = 1;
	free_ast(res.tree);
	free_token_list(&tokens);
	lst_clear_cmd(&data->cmd);
}

static void	shell_loop(t_data *data)
{
	char	*line;

	while (1)
	{
		g_signal = 0;
		set_dad_signals();
		line = readline(PROMPT);
		if (!line)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (g_signal == SIGINT)
			data->last_exit_code = 130;
		run_line(data, line);
		free(line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		status;

	(void)argv;
	if (argc != 1)
		return (usage_message(true));
	ft_memset(&data, 0, sizeof(data));
	if (!init_data(&data, env))
		return (1);
	data.interactive = isatty(STDIN_FILENO);
	shell_loop(&data);
	status = data.last_exit_code;
	free_data(&data, true);
	return (status);
}
/*
int     main(void)
{
        // char s[] = "|";
        // char c = 'm';
        // printf("%d\n",get_token_type(s));
        // printf("%d\n",is_space_to_skip(c));
        // char    *line;
        // t_token *t_token_list;
        // line = "ls -a |     car -e| wc -l && ls | echo 'echec  | || && ou'aiiiii''";
        // t_token_list = tokenizer(line);
        // print_token_list(t_token_list);
        char	*line;
	t_token		*token_list;
	t_ast_res	res;

	while (1)
        {
                line =  readline("ceci est un prompt>");
                if (!line)
                        return 0;
                token_list = tokenizer(line);
                //print_token_list(token_list);
                res = ast_builder(token_list, TOKEN_NONE);
                (void)res;
		free(line);
        }
        return (0);
*/
