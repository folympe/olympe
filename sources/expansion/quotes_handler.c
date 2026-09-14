/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 13:59:58 by olfhal            #+#    #+#             */
/*   Updated: 2026/09/06 06:30:31 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_len(char *str, int count, int i)
{
	int	status;

	status = DEFAULT;
	while (str[i])
	{
		if (status == DEFAULT && (str[i] == '\'' || str[i] == '\"'))
			status = (str[i] == '\'') * SQUOTE
				+ (str[i] == '\"') * DQUOTE;
		else if ((status == SQUOTE && str[i] == '\'')
			|| (status == DQUOTE && str[i] == '\"'))
			status = DEFAULT;
		else
			count++;
		i++;
	}
	return (count + 1);
}

bool	quotes_in_string(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '\'' || str[i] == '\"')
			return (true);
	return (false);
}

int	handle_quotes(t_data *data)
{
	t_expand_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if ((!tmp->prev || tmp->prev->type != HEREDOC)
			&& quotes_in_string(tmp->str))
			remove_quotes(&tmp);
		tmp = tmp->next;
	}
	return (0);
}
