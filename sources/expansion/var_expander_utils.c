/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:03:49 by olfhal            #+#    #+#             */
/*   Updated: 2026/08/31 14:03:51 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_var_value(char *new_str, char *var_value, int *j)
{
	char	*dst;
	char	*src;

	dst = new_str + *j;
	src = var_value;
	while (*src)
		*dst++ = *src++;
	*j = dst - new_str;
}

char	*get_new_token_string(char *oldstr, char *var_value,
		int newstr_size, int index)
{
	char	*new_str;
	char	*dst;
	int		i;

	new_str = malloc(sizeof(char) * newstr_size);
	if (!new_str)
		return (NULL);
	dst = new_str;
	i = 0;
	while (oldstr[i])
	{
		if (i == index && oldstr[i] == '$')
		{
			copy_var_value(new_str, var_value, (int *)&(int){dst - new_str});
			dst += ft_strlen(var_value);
			i += var_length(oldstr + index) + 1;
			continue ;
		}
		*dst++ = oldstr[i++];
	}
	*dst = '\0';
	return (new_str);
}
