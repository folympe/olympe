/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identify_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 13:58:55 by olfhal            #+#    #+#             */
/*   Updated: 2026/08/31 13:58:57 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_var_compliant(char c)
{
	return (ft_isalnum(c) || c == '_');
}

int	var_length(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (0);
	i++;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (1);
	while (str[i] && is_var_compliant(str[i]))
	{
		count++;
		i++;
	}
	return (count);
}

char	*identify_var(char *str)
{
	char	*var;
	char	*tmp;
	int		i;

	i = 0;
	while (str[i] && str[i] != '$')
		i++;
	if (!str[i])
		return (NULL);
	i++;
	var = ft_substr(str, i, var_length(str));
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	free_ptr(var);
	return (tmp);
}
