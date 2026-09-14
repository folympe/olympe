/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:11:59 by olfhal            #+#    #+#             */
/*   Updated: 2026/07/01 16:12:02 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_builtin(t_data *data, char **args)
{
	int	i;
	int	idx;
	int	ret;

	i = 1;
	ret = EXIT_SUCCESS;
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i])
			|| ft_strchr(args[i], '=') != NULL)
		{
			errmsg_cmd("unset", args[i],
				"not a valid identifier", false);
			ret = EXIT_FAILURE;
		}
		else
		{
			idx = get_env_var_index(data->env, args[i]);
			if (idx != -1)
				remove_env_var(data, idx);
		}
		i++;
	}
	return (ret);
}
