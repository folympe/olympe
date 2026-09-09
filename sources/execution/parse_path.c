/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 13:53:58 by olfhal            #+#    #+#             */
/*   Updated: 2026/08/31 13:54:02 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_valid_cmd_path(char *cmd, char **paths)
{
	int		i;
	char	*cmd_path;

	i = -1;
	while (paths[++i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
		{
			errmsg_cmd("malloc", NULL,
				"an unexpected error occured", EXIT_FAILURE);
			return (NULL);
		}
		if (!access(cmd_path, F_OK | X_OK))
			return (cmd_path);
		free_ptr(cmd_path);
	}
	return (NULL);
}

static char	**get_paths_from_env(t_data *data)
{
	char	*path;
	char	**env_paths;

	path = get_env_var_value(data->env, "PATH");
	if (!path || get_env_var_index(data->env, "PATH") == -1)
		return (NULL);
	env_paths = ft_split(path, ':');
	return (env_paths);
}

char	*get_cmd_path(t_data *data, char *name)
{
	char	**env_paths;
	char	*cmd;
	char	*cmd_path;

	if (!name)
		return (NULL);
	env_paths = get_paths_from_env(data);
	if (!env_paths)
		return (NULL);
	cmd = ft_strjoin("/", name);
	if (!cmd)
	{
		free_str_tab(env_paths);
		return (NULL);
	}
	cmd_path = find_valid_cmd_path(cmd, env_paths);
	free_ptr(cmd);
	free_str_tab(env_paths);
	return (cmd_path);
}
