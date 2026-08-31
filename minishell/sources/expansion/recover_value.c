/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:00:41 by olfhal            #+#    #+#             */
/*   Updated: 2026/08/31 14:00:43 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	var_exists(t_data *data, char *var)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var);
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], var, len))
			return (0);
	}
	return (1);
}

static char	*search_env_var(t_data *data, char *var)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(var);
	while (data->env[++i])
	{
		if (!ft_strncmp(data->env[i], var, len))
			return (ft_strdup(data->env[i] + len));
	}
	return (NULL);
}

char	*recover_val(t_token *token, char *str, t_data *data)
{
	char	*value;
	char	*var;

	value = NULL;
	var = identify_var(str);
	if (var)
	{
		if (var_exists(data, var) == 0)
		{
			if (token)
				token->var_exists = true;
			value = search_env_var(data, var);
		}
		else if (var[0] == '?' && var[1] == '=')
			value = ft_itoa(g_last_exit_code);
	}
	free_ptr(var);
	return (value);
}
