/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:09:31 by olfhal            #+#    #+#             */
/*   Updated: 2026/07/01 16:09:35 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_builtin(t_data *data, char **args)
{
	int	i;

	if (args && args[1])
		return (errmsg_cmd("env", NULL, "too many arguments", 2));
	if (!data->env)
		return (EXIT_FAILURE);
	i = -1;
	while (data->env[++i] != NULL)
	{
		ft_putendl_fd(data->env[i], STDOUT_FILENO);
	}
	return (EXIT_SUCCESS);
}
