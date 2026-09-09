/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 08:10:01 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 08:10:22 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token_list(t_token **tokens)
{
	t_token	*next;

	if (!tokens)
		return ;
	while (*tokens)
	{
		next = (*tokens)->next;
		free((void *)(*tokens)->word);
		free(*tokens);
		*tokens = next;
	}
}

void	free_expand_token_list(t_expand_token **tokens)
{
	t_expand_token	*next;

	if (!tokens)
		return ;
	while (*tokens)
	{
		next = (*tokens)->next;
		free_ptr((*tokens)->str);
		free_ptr((*tokens)->str_backup);
		free(*tokens);
		*tokens = next;
	}
}

static void	free_redirs(t_redir *redir)
{
	t_redir	*next;

	while (redir)
	{
		next = redir->next;
		if (redir->heredoc_file)
			unlink(redir->heredoc_file);
		free_ptr(redir->word);
		free_ptr(redir->heredoc_file);
		free(redir);
		redir = next;
	}
}

static void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->subshell)
		lst_clear_cmd(&cmd->subshell);
	free_ptr(cmd->path);
	free_str_tab(cmd->args);
	free_io(cmd->io_fds);
	free_redirs(cmd->redirs);
	free_ptr(cmd->pipe_fd);
	free(cmd);
}

void	lst_clear_cmd(t_command **cmds)
{
	t_command	*next;

	if (!cmds)
		return ;
	while (*cmds)
	{
		next = (*cmds)->next;
		free_command(*cmds);
		*cmds = next;
	}
}
