/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 07:45:02 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 07:45:05 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cmd_args(t_command *cmd)
{
	int	i;

	if (!cmd->args)
		return ;
	i = 0;
	while (cmd->args[i])
	{
		printf("\tArgs[%d] = %s\n", i, cmd->args[i]);
		i++;
	}
}

static void	print_cmd_io(t_command *cmd)
{
	if (!cmd->io_fds)
		return ;
	if (cmd->io_fds->infile)
	{
		printf("\tInfile: %s\n", cmd->io_fds->infile);
		printf("\t\tfd_in: %d\n", cmd->io_fds->fd_in);
	}
	if (cmd->io_fds->heredoc_delimiter)
		printf("\tHeredoc delimiter: %s\n",
			cmd->io_fds->heredoc_delimiter);
	if (cmd->io_fds->outfile)
	{
		printf("\tOutfile: %s\n", cmd->io_fds->outfile);
		printf("\t\tfd_out: %d\n", cmd->io_fds->fd_out);
	}
}

void	print_cmd_list(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	printf("\n---- COMMAND LIST ----\n");
	while (cmd)
	{
		printf("--- Command = %s\n", cmd->command);
		print_cmd_args(cmd);
		printf("\tPipe_output = %d\n", cmd->pipe_output);
		print_cmd_io(cmd);
		if (!cmd->prev)
			printf("\tprev = NULL\n");
		else
			printf("\tprev = %s\n", cmd->prev->command);
		if (!cmd->next)
			printf("\tnext = NULL\n");
		else
			printf("\tnext = %s\n", cmd->next->command);
		printf("\n");
		cmd = cmd->next;
	}
	printf("\n");
}

void	print_token_type(t_token *token, char *prefix)
{
	printf("%s", prefix);
	printf("%s\n", get_token_name(token->type));
}

void	print_token_list(t_token *tokens)
{
	int	i;

	i = 0;
	printf("\n---- TOKEN LIST ----\n");
	while (tokens)
	{
		printf("--- Token [%d] [%p]\n", i, (void *)tokens);
		printf("\tWord = [%s]\n", tokens->word);
		print_token_type(tokens, "\tType = ");
		if (tokens->next)
			printf("\tNext = [%p]\n", (void *)tokens->next);
		else
			printf("\tNext = NULL\n");
		i++;
		tokens = tokens->next;
	}
}
