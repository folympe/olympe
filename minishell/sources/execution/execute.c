/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 13:52:36 by olfhal            #+#    #+#             */
/*   Updated: 2026/08/31 13:52:39 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd, false);
	save_status = 0;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == -1)
		{
			if (errno == ECHILD)
				break ;
			continue ;
		}
		if (wpid == data->pid)
			save_status = status;
	}
	if (WIFSIGNALED(save_status))
		return (128 + WTERMSIG(save_status));
	if (WIFEXITED(save_status))
		return (WEXITSTATUS(save_status));
	return (save_status);
}

static int	create_children(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	while (cmd && data->pid != 0)
	{
		data->pid = fork();
		if (data->pid < 0)
			return (errmsg_cmd("fork", NULL,
					strerror(errno), EXIT_FAILURE));
		if (data->pid == 0)
			execute_command(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}

static int	prep_for_exec(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (data->cmd->command)
	{
		if (!create_pipes(data))
			return (EXIT_FAILURE);
		return (CMD_NOT_FOUND);
	}
	if (data->cmd->io_fds
		&& !check_infile_outfile(data->cmd->io_fds))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	execute(t_data *data)
{
	int	ret;

	ret = prep_for_exec(data);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!data->cmd->pipe_output && !data->cmd->prev)
	{
		if (check_infile_outfile(data->cmd->io_fds))
		{
			redirect_io(data->cmd->io_fds);
			ret = execute_builtin(data, data->cmd);
			restore_io(data->cmd->io_fds);
		}
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_children(data));
}
