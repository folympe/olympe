/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 13:53:19 by olfhal            #+#    #+#             */
/*   Updated: 2026/08/31 13:53:21 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	cmd_is_dir(char *cmd)
{
	struct stat	info;

	ft_memset(&info, 0, sizeof(struct stat));
	stat(cmd, &info);
	return (S_ISDIR(info.st_mode));
}

int	check_command_not_found(t_data *data, t_command *cmd)
{
	char	*name;

	name = cmd->command;
	if (!ft_strchr(name, '/') && get_env_var_index(data->env, "PATH") != -1)
		return (errmsg_cmd(name, NULL, "command not found",
				CMD_NOT_FOUND));
	if (access(name, F_OK))
		return (errmsg_cmd(name, NULL, strerror(errno), CMD_NOT_FOUND));
	if (cmd_is_dir(name))
		return (errmsg_cmd(name, NULL, "Is a directory",
				CMD_NOT_EXECUTABLE));
	if (access(name, F_OK | X_OK))
		return (errmsg_cmd(name, NULL, strerror(errno),
				CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}
