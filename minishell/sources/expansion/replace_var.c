/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_var.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:02:05 by olfhal            #+#    #+#             */
/*   Updated: 2026/08/31 14:02:08 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	erase_var(t_token **token_node, char *str, int index)
{
	char	*new_str;
	int		i;
	int		j;
	int		skip;

	i = 0;
	j = 0;
	skip = var_length(str + index) + 1;
	new_str = malloc(sizeof(char)
			* (ft_strlen(str) - skip + 1));
	if (!new_str)
		return (1);
	while (str[i])
	{
		if (i == index && str[i] == '$')
			i += skip;
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free_ptr((*token_node)->str);
	(*token_node)->str = new_str;
	return (0);
}

static char	*erase_and_replace(t_token **token_node, char *str,
			char *var_value, int index)
{
	char	*newstr;

	newstr = get_new_token_string(str, var_value,
			ft_strlen(str) + ft_strlen(var_value)
			- var_length(str + index), index);
	if (token_node && *token_node)
	{
		free_ptr((*token_node)->str);
		(*token_node)->str = newstr;
	}
	return (newstr);
}

int	replace_var(t_token **token_node, char *var_value, int index)
{
	int	ret;

	ret = 0;
	if (!var_value)
		ret = erase_var(token_node, (*token_node)->str, index);
	else if (!erase_and_replace(token_node, (*token_node)->str,
			var_value, index))
		ret = 0;
	else
		ret = 1;
	free_ptr(var_value);
	return (ret);
}

char	*replace_str_heredoc(char *str, char *var_value, int index)
{
	char	*old;

	if (!var_value)
	{
		if (str)
			str[0] = '\0';
		return (free_ptr(var_value), str);
	}
	old = str;
	str = erase_and_replace(NULL, str, var_value, index);
	free_ptr(old);
	free_ptr(var_value);
	return (str);
}
