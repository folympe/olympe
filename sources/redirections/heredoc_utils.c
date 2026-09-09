/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 00:37:31 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 09:32:41 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	same_delimiter(char *line, char *delimiter)
{
	if (ft_strlen(line) != ft_strlen(delimiter))
		return (false);
	return (ft_strncmp(line, delimiter, ft_strlen(line) + 1) == 0);
}

static bool	check_heredoc_line(t_data *data, char **line, t_io_fds *io)
{
	if (!*line)
	{
		errmsg_cmd("Warning", io->heredoc_delimiter, "here-document delimited by end-of-file", 0);
		return (false);
	}
	if (same_delimiter(*line, io->heredoc_delimiter))
		return (false);
	if (!io->heredoc_quotes && ft_strchr(*line, '$'))
	{
		*line = var_expander_heredoc(data, *line);
		if (!*line)
			return (false);
	}
	return (true);
}

static void	restore_heredoc(int stdin_cpy)
{
	dup2(stdin_cpy, STDIN_FILENO);
	close(stdin_cpy);
	set_dad_signals();
}

bool	fill_heredoc(t_data *data, t_io_fds *io, int fd)
{
	char	*line;
	int	stdin_cpy;

	stdin_cpy = dup(STDIN_FILENO);
	if (stdin_cpy == -1)
		return (false);
	g_signal = 0;
	set_heredoc_signals();
	line = readline("> ");
	while (g_signal != SIGINT && check_heredoc_line(data, &line, io))
	{
		ft_putendl_fd(line, fd);
		free_ptr(line);
		line = readline("> ");
	}
	free_ptr(line);
	restore_heredoc(stdin_cpy);
	if (g_signal == SIGINT)
		data->last_exit_code = 130;
	return (g_signal != SIGINT);
}
