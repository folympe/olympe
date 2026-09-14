/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 08:59:51 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 09:07:27 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_builtin(t_data *data, t_command *cmd)
{
	char	*name;

	name = cmd->command;
	if (!ft_strncmp(name, "cd", 3))
		return (cd_builtin(data, cmd->args));
	if (!ft_strncmp(name, "echo", 5))
		return (echo_builtin(data, cmd->args));
	if (!ft_strncmp(name, "env", 4))
		return (env_builtin(data, cmd->args));
	if (!ft_strncmp(name, "export", 7))
		return (export_builtin(data, cmd->args));
	if (!ft_strncmp(name, "pwd", 4))
		return (pwd_builtin(data, cmd->args));
	if (!ft_strncmp(name, "unset", 6))
		return (unset_builtin(data, cmd->args));
	if (!ft_strncmp(name, "exit", 5))
		return (exit_builtin(data, cmd->args));
	return (CMD_NOT_FOUND);
}

static int	execute_sys_bin(t_data *data, t_command *cmd)
{
	if (!cmd->command || !*cmd->command || cmd_is_dir(cmd->command))
		return (CMD_NOT_FOUND);
	cmd->path = get_cmd_path(data, cmd->command);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->args, data->env) == -1)
	{
		errmsg_cmd("execve", NULL, strerror(errno), errno);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	execute_local_bin(t_data *data, t_command *cmd)
{
	int	status;

	status = check_command_not_found(data, cmd);
	if (status)
		return (status);
	if (execve(cmd->command, cmd->args, data->env) != -1)
		return (EXIT_SUCCESS);
	return (errmsg_cmd("execve", NULL, strerror(errno), errno));
}

static void	execute_subshell(t_data *data, t_command *cmd)
{
	int	status;

	if (!check_infile_outfile(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	if (!set_pipe_fds(data->cmd, cmd) || !redirect_io(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	close_fds(data->cmd, false);
	data->cmd = cmd->subshell;
	status = execute(data);
	exit_shell(data, status);
}

int	execute_command(t_data *data, t_command *cmd)
{
	int	status;

	if (!cmd)
		exit_shell(data, EXIT_FAILURE);
	if (cmd->is_subshell)
		execute_subshell(data, cmd);
	if (!cmd->command)
		exit_shell(data, errmsg_cmd("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	if (!check_infile_outfile(cmd->io_fds)
		|| !set_pipe_fds(data->cmd, cmd) || !redirect_io(cmd->io_fds))
		exit_shell(data, EXIT_FAILURE);
	close_fds(data->cmd, false);
	status = CMD_NOT_FOUND;
	if (!ft_strchr(cmd->command, '/'))
		status = execute_builtin(data, cmd);
	if (!ft_strchr(cmd->command, '/') && status == CMD_NOT_FOUND)
		status = execute_sys_bin(data, cmd);
	if (status == CMD_NOT_FOUND)
		status = execute_local_bin(data, cmd);
	exit_shell(data, status);
	return (status);
}
