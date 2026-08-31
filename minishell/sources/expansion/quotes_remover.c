/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_remover.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:00:19 by olfhal            #+#    #+#             */
/*   Updated: 2026/08/31 14:00:21 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	change_status_to_quote(t_token **token_node, int *i)
{
	if ((*token_node)->str[*i] == '\'')
		(*token_node)->status = SQUOTE;
	else if ((*token_node)->str[*i] == '\"')
		(*token_node)->status = DQUOTE;
	(*i)++;
}

static bool	if_quotes_and_default(t_token **token_node, int i)
{
	return (((*token_node)->str[i] == '\''
			|| (*token_node)->str[i] == '\"')
		&& (*token_node)->status == DEFAULT);
}

static bool	change_back_to_default(t_token **token_node, int *i)
{
	char	c;

	c = (*token_node)->str[*i];
	if ((c == '\'' && (*token_node)->status == SQUOTE)
		|| (c == '\"' && (*token_node)->status == DQUOTE))
	{
		(*token_node)->status = DEFAULT;
		(*i)++;
		return (true);
	}
	return (false);
}

int	remove_quotes(t_token **token_node)
{
	char	*new_line;
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (*token_node)->str;
	new_line = malloc(sizeof(char) * count_len(str, 0, 0));
	if (!new_line)
		return (1);
	while (str[i])
	{
		if (if_quotes_and_default(token_node, i))
			change_status_to_quote(token_node, &i);
		else if (change_back_to_default(token_node, &i))
			;
		else
			new_line[j++] = str[i++];
	}
	new_line[j] = '\0';
	free_ptr((*token_node)->str);
	(*token_node)->str = new_line;
	(*token_node)->join = true;
	return (0);
}
