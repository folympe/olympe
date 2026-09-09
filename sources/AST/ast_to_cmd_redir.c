/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmd_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 21:47:24 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 05:40:19 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_to_cmd.h"

static t_redir	*new_redir(t_node *node)
{
	t_redir		*redir;

	redir = ft_calloc(1, sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = node->type;
	redir->word = ft_strdup((char *)node->data.word);
	if (!redir->word)
	{
		free(redir);
		return (NULL);
	}
	return (redir);
}

static void	clean_heredoc_io(t_io_fds *io)
{
	if (io->fd_in != -1)
		close(io->fd_in);
	free_ptr(io->heredoc_delimiter);
	if (io->infile)
		unlink(io->infile);
	free_ptr(io->infile);
}

static bool save_heredoc(t_data *data, t_redir *redir)
{
	t_io_fds	io;

	ft_memset(&io, 0, sizeof(io));
	io.fd_in = -1;
	io.fd_out = -1;
	io.stdin_backup = -1;
	io.stdout_backup = -1;
	if (!prepare_heredoc(data, &io, redir->word))
	{
		clean_heredoc_io(&io);
		return (false);
	}
	if (io.fd_in != -1)
		close(io.fd_in);
	redir->heredoc_file = io.infile;
	io.infile = NULL;
	free_ptr(io.heredoc_delimiter);
	return (true);
}

static void	append_redir(t_command *cmd, t_redir *new_redir)
{
	t_redir		*last;

	if (!cmd->redirs)
	{
		cmd->redirs = new_redir;
		return ;
	}
	last = cmd->redirs;
	while (last->next)
		last = last->next;
	last->next = new_redir;
}

bool	ast_add_redir(t_data *data, t_command *cmd, t_node *node)
{
	t_redir		*redir;

	redir = new_redir(node);
	if (!redir)
		return (false);
	if (node->type == TOKEN_HEREDOC && !save_heredoc(data, redir))
	{
		free_ptr(redir->word);
		free(redir);
		return (false);
	}
	append_redir(cmd, redir);
	return (true);
}
