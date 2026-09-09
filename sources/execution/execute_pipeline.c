/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 07:37:02 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 07:37:28 by jiasmoun         ###   ########.fr       */
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
		if (wpid == -1 && errno == ECHILD)
			break ;
		if (wpid == -1)
			continue ;
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
	data->pid = -1;
	while (cmd)
	{
		data->pid = fork();
		if (data->pid < 0)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		if (data->pid == 0)
		{
			set_son_signals();
			execute_command(data, cmd);
		}
		cmd = cmd->next;
	}
	return (get_children(data));
}

static int	run_parent_builtin(t_data *data)
{
	int	ret;

	if (!check_infile_outfile(data->cmd->io_fds))
		return (EXIT_FAILURE);
	if (!redirect_io(data->cmd->io_fds))
		return (EXIT_FAILURE);
	ret = execute_builtin(data, data->cmd);
	restore_io(data->cmd->io_fds);
	return (ret);
}

static int	run_children(t_data *data)
{
	int	ret;

	signal(SIGINT, SIG_IGN); signal(SIGQUIT, SIG_IGN);
	ret = create_children(data);
	set_dad_signals();
	return (ret);
}

int	execute_pipeline(t_data *data)
{
	int	ret;

	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->command && !data->cmd->is_subshell && !data->cmd->next)
		return (check_infile_outfile(data->cmd->io_fds) == false);
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	ret = CMD_NOT_FOUND;
	if (!data->cmd->next && data->cmd->command)
		ret = run_parent_builtin(data);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (run_children(data));
}
