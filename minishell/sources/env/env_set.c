/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 17:41:26 by olfhal            #+#    #+#             */
/*   Updated: 2026/07/01 17:41:30 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**realloc_env_vars(t_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof(*new_env));
	if (!new_env)
		return (NULL);
	i = -1;
	while (data->env[++i] && i < size)
	{
		new_env[i] = ft_strdup(data->env[i]);
		free_ptr(data->env[i]);
	}
	free(data->env);
	return (new_env);
}

bool	set_env_var(t_data *data, char *key, char *value)
{
	int		idx;
	char	*tmp;
	int		size;

	idx = get_env_var_index(data->env, key);
	if (!value)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (idx != -1 && data->env[idx])
	{
		free_ptr(data->env[idx]);
		data->env[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		size = env_var_count(data->env);
		data->env = realloc_env_vars(data, size + 1);
		if (!data->env)
			return (false);
		data->env[size] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

bool	remove_env_var(t_data *data, int idx)
{
	int	i;
	int	size;

	size = env_var_count(data->env);
	if (idx < 0 || idx >= size)
		return (false);
	free_ptr(data->env[idx]);
	i = idx;
	while (data->env[i + 1])
	{
		data->env[i] = ft_strdup(data->env[i + 1]);
		free_ptr(data->env[i + 1]);
		i++;
	}
	data->env = realloc_env_vars(data, size - 1);
	if (!data->env)
		return (false);
	return (true);
}
