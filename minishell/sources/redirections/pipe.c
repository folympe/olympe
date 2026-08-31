/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:12:30 by olfhal            #+#    #+#             */
/*   Updated: 2026/08/31 14:12:33 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_fds(t_command *cmds, t_command *skip_cmd)
{
	while (cmds)
	{
		if (cmds->pipe_fd && cmds != skip_cmd)
		{
			close(cmds->pipe_fd[0]);
			close(cmds->pipe_fd[1]);
		}
		cmds = cmds->next;
	}
}

bool	create_pipes(t_data *data)
{
	t_command	*tmp;
	int			*fd;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_output
			|| (tmp->prev && tmp->prev->pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) == -1)
			{
				free(fd);
				free_data(data, false);
				return (false);
			}
			tmp->pipe_fd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	set_pipe_fds(t_command *cmds, t_command *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_output)
	{
		if (dup2(c->prev->pipe_fd[0], STDIN_FILENO) == -1)
			return (false);
	}
	if (c->pipe_output)
	{
		if (dup2(c->pipe_fd[1], STDOUT_FILENO) == -1)
			return (false);
	}
	close_pipe_fds(cmds, c);
	return (true);
}
