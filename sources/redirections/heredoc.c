/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 04:14:14 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 10:05:57 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	get_heredoc(t_data *data, t_io_fds *io)
{
	int	fd;

	fd = open(io->infile, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
	{
		perror(io->infile);
		return (false);
	}
	if (!fill_heredoc(data, io, fd))
	{
		close(fd);
		unlink(io->infile);
		return (false);
	}
	close(fd);
	return (true);
}

static char	*get_heredoc_name(void)
{
	char	*name;
	char	*id;
	int	count;

	count = 0;
	while (1)
	{
		id = ft_itoa(count);
		if (!id)
			return (NULL);
		name = ft_strjoin(HEREDOC_NAME, id);
		free(id);
		if (!name)
			return (NULL);
		if (access(name, F_OK) == -1)
			return (name);
		free(name);
		count++;
	}
}

static char	*get_delim(const char *delim, bool *quotes)
{
	int	last;

	last = (int)ft_strlen(delim) - 1;
	if (last < 0 || delim[0] != delim[last])
		return (ft_strdup((char *)delim));
	if (delim[0] != '\'' && delim[0] != '"')
		return (ft_strdup((char *)delim));
	*quotes = true;
	return (ft_strtrim(delim, "\'\""));
}

static void	clear_input(t_io_fds *io)
{
	if (io->fd_in != -1)
	close(io->fd_in);
	if (io->heredoc_delimiter && io->infile)
		unlink(io->infile);
	free_ptr(io->infile);
	free_ptr(io->heredoc_delimiter);
	io->infile = NULL;
	io->heredoc_delimiter = NULL;
	io->heredoc_quotes = false;
	io->fd_in = -1;
}

bool	prepare_heredoc(t_data *data, t_io_fds *io, const char *delimiter)
{
	clear_input(io);
	io->infile = get_heredoc_name();
	if (!io->infile)
		return (false);
	io->heredoc_delimiter = get_delim(delimiter, &io->heredoc_quotes);
	if (!io->heredoc_delimiter || !get_heredoc(data, io))
	{
		clear_input(io);
		return (false);
	}
	io->fd_in = open(io->infile, O_RDONLY);
	if (io->fd_in == -1)
	{
		perror(io->infile);
		clear_input(io);
		return (false);
	}
	return (true);
}
