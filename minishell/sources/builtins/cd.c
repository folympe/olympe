/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:08:04 by olfhal            #+#    #+#             */
/*   Updated: 2026/07/01 16:08:09 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_wds(t_data *data, char *wd)
{
	char	*pwd_val;

	pwd_val = get_env_var_value(data->env, "PWD");
	set_env_var(data, "OLDPWD", pwd_val);
	set_env_var(data, "PWD", wd);
	if (data->old_working_dir)
	{
		free_ptr(data->old_working_dir);
		data->old_working_dir = NULL;
		data->old_working_dir = ft_strdup(data->working_dir);
	}
	if (data->working_dir)
		free_ptr(data->working_dir);
	data->working_dir = ft_strdup(wd);
	free_ptr(wd);
}

static	bool	chdir_errno_mod(char *path)
{
	int	err;

	if (errno == ESTALE)
		errno = ENOENT;
	err = errno;
	errmsg_cmd("cd", path, strerror(err), err);
	return (false);
}

static bool	change_dir(t_data *data, char *path)
{
	char	cwd[PATH_MAX];
	char	*ret;
	char	*tmp;

	if (chdir(path))
		return (chdir_errno_mod(path));
	ret = getcwd(cwd, PATH_MAX);
	if (ret)
		ret = ft_strdup(cwd);
	else
	{
		errmsg_cmd("cd: error retrieving current directory",
			"getcwd: cannot access parent directories",
			strerror(errno), errno);
		tmp = ft_strjoin(data->working_dir, "/");
		ret = ft_strjoin(tmp, path);
		free_ptr(tmp);
	}
	update_wds(data, ret);
	return (true);
}

int	cd_builtin(t_data *data, char **args)
{
	char	*path;

	path = NULL;
	if (args && args[1] && !ft_isspace(args[1][0])
		&& args[1][0] != '\0' && ft_strncmp(args[1], "--", 3) != 0)
	{
		if (args[2])
			return (errmsg_cmd("cd", NULL, "too many arguments", EXIT_FAILURE));
		if (ft_strncmp(args[1], "-", 2) == 0)
		{
			path = get_env_var_value(data->env, "OLDPWD");
			if (!path)
				return (errmsg_cmd("cd", NULL, "OLDPWD not set", EXIT_FAILURE));
		}
		else
			path = args[1];
	}
	else
	{
		path = get_env_var_value(data->env, "HOME");
		if (!path || *path == '\0' || ft_isspace(*path))
			return (errmsg_cmd("cd", NULL, "HOME not set", EXIT_FAILURE));
	}
	return (!change_dir(data, path));
}
