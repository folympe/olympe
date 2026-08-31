/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:11:09 by olfhal            #+#    #+#             */
/*   Updated: 2026/07/01 16:11:12 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**get_key_value_pair(char *arg)
{
	char	**tmp;
	char	*eq_pos;
	size_t	key_len;

	eq_pos = ft_strchr(arg, '=');
	key_len = eq_pos - arg;
	tmp = malloc(sizeof(*tmp) * 3);
	if (!tmp)
		return (NULL);
	tmp[0] = ft_substr(arg, 0, key_len);
	tmp[1] = ft_substr(eq_pos + 1, 0, ft_strlen(eq_pos + 1));
	tmp[2] = NULL;
	return (tmp);
}

int	export_builtin(t_data *data, char **args)
{
	int		i;
	char	**tmp;
	int		ret;

	i = 1;
	ret = EXIT_SUCCESS;
	if (!args[i])
		return (env_builtin(data, NULL));
	while (args[i])
	{
		if (!is_valid_env_var_key(args[i]))
			ret = (errmsg_cmd("exp", args[i],
						"not valid", false), EXIT_FAILURE);
		else if (ft_strchr(args[i], '='))
		{
			tmp = get_key_value_pair(args[i]);
			set_env_var(data, tmp[0], tmp[1]);
			free_str_tab(tmp);
		}
		i++;
	}
	return (ret);
}
