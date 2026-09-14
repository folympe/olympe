/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recover_value.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 06:45:06 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 06:45:41 by jiasmoun         ###   ########.fr       */
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

char	*recover_val(t_expand_token *token, char *str, t_data *data)
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
			value = ft_itoa(data->last_exit_code);
	}
	free_ptr(var);
	return (value);
}
