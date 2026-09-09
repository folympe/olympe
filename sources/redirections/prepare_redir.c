/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 23:58:52 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 14:00:20 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void clear_input(t_io_fds *io)
{
	if (io->fd_in != -1)
		close(io->fd_in);
	if (io->heredoc_delimiter && io->infile)
		unlink(io->infile);
	free_ptr(io->infile);
	free_ptr(io->heredoc_delimiter);
	io->infile = NULL;
	io->heredoc_delimiter = NULL;
	io->fd_in = -1;
}

static bool	set_input(t_data *data, t_io_fds *io, t_redir *redir)
{
	clear_input(io);
	io->infile = expand_word(data, redir->word);
	if (!io->infile)
		return (false);
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
	{
		perror(io->infile);
		return (false);
	}
	return (true);
}

static bool	set_output(t_data *data, t_io_fds *io, t_redir *redir)
{
	int flags;

	if (io->fd_out != -1)
		close(io->fd_out);
	free_ptr(io->outfile);
	io->outfile = expand_word(data, redir->word);
	if (!io->outfile)
		return (false);
	flags = O_CREAT | O_WRONLY | O_TRUNC;
	if (redir->type == TOKEN_REDIRECT_APPEND)
		flags = O_CREAT | O_WRONLY | O_APPEND;
	io->fd_out = open(io->outfile, flags, 0644);
	if (io->fd_out == -1)
	{
		perror(io->outfile);
		return (false);
	}
	return (true);
}

static bool	set_heredoc(t_io_fds *io, t_redir *redir)
{
	clear_input(io);
	io->infile = ft_strdup(redir->heredoc_file);
	io->heredoc_delimiter = ft_strdup(redir->word);
	if (!io->infile || !io->heredoc_delimiter)
		return (false);
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
		return (false);
	return (true);
}

bool	prepare_command_redirs(t_data *data, t_command *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->type == TOKEN_REDIRECT_IN && !set_input(data, cmd->io_fds, redir))
			return (false);
		if ((redir->type == TOKEN_REDIRECT_OUT || redir->type == TOKEN_REDIRECT_APPEND) && !set_output(data, cmd->io_fds, redir))
			return (false);
		if (redir->type == TOKEN_HEREDOC && !set_heredoc(cmd->io_fds, redir))
			return (false);
		redir = redir->next;
	}
	return (true);
}
