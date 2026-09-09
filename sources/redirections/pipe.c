/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 00:28:04 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 10:07:46 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_pipe_fds(t_command *cmds, t_command *skip_cmd)
{
	(void)skip_cmd;
	
	while (cmds)
	{
		if (cmds->pipe_fd)
		{
			if (cmds->pipe_fd[0] != -1)
				close(cmds->pipe_fd[0]);
			if (cmds->pipe_fd[1] != -1)
				close(cmds->pipe_fd[1]);
			cmds->pipe_fd[0] = -1;
			cmds->pipe_fd[1] = -1;
		}
		cmds = cmds->next;
	}
}

bool	create_pipes(t_data *data)
{
	t_command	*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_output)
		{
			tmp->pipe_fd = malloc(sizeof(int) * 2);
			if (!tmp->pipe_fd || pipe(tmp->pipe_fd) == -1)
			{
				free_ptr(tmp->pipe_fd);
				tmp->pipe_fd = NULL;
				return (false);
			}
		}
		tmp = tmp->next;
	}
	return (true);
}

bool	set_pipe_fds(t_command *cmds, t_command *cmd)
{
	(void)cmds;

	if (!cmd)
		return (false);
	if (cmd->prev && cmd->prev->pipe_output && dup2(cmd->prev->pipe_fd[0], STDIN_FILENO) == -1)
		return (false);
	if (cmd->pipe_output && dup2(cmd->pipe_fd[1], STDOUT_FILENO) == -1)
		return (false);
	return (true);
}
