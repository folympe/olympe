/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 17:41:44 by olfhal            #+#    #+#             */
/*   Updated: 2026/07/01 17:41:48 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_var_count(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
		i++;
	return (i);
}

int	get_env_var_index(char **env, char *var)
{
	int		i;
	char	*tmp;
	size_t	len;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (-1);
	len = ft_strlen(tmp);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(tmp, env[i], len))
		{
			free_ptr(tmp);
			return (i);
		}
		i++;
	}
	free_ptr(tmp);
	return (-1);
}

char	*get_env_var_value(char **env, char *var)
{
	int		i;
	char	*tmp;
	size_t	len;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	len = ft_strlen(tmp);
	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(tmp, env[i], len))
		{
			free_ptr(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}

bool	is_valid_env_var_key(char *var)
{
	int	i;

	if (!var || (!ft_isalpha(var[0]) && var[0] != '_'))
		return (false);
	i = 1;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}
