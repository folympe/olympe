/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_expander.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 06:47:14 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 10:12:11 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_status(t_expand_token **token_node, char c)
{
	int	status;

	status = (*token_node)->status;
	if (c == '\'')
	{
		if (status == DEFAULT)
			(*token_node)->status = SQUOTE;
		else if (status == SQUOTE)
			(*token_node)->status = DEFAULT;
	}
	else if (c == '\"')
	{
		if (status == DEFAULT)
			(*token_node)->status = DQUOTE;
		else if (status == DQUOTE)
			(*token_node)->status = DEFAULT;
	}
}

static bool	is_next_char_a_sep(char c)
{
	char	*sep;

	sep = "$ =";
	while (*sep)
	{
		if (*sep == c)
			return (true);
		sep++;
	}
	return (c == '\0');
}

static bool	var_between_quotes(char *str, int i)
{
	char	*ptr;

	if (i <= 0)
		return (false);
	ptr = str + i;
	return (*(ptr - 1) == '\"' && *(ptr + 1) == '\"');
}

int	expand_token_word(t_data *data, t_expand_token **cur)
{
	int	i;

	i = 0;
	while ((*cur)->str[i])
	{
		update_status(cur, (*cur)->str[i]);
		if ((*cur)->str[i] == '$'
			&& !is_next_char_a_sep((*cur)->str[i + 1])
			&& !var_between_quotes((*cur)->str, i)
			&& ((*cur)->status == DEFAULT || (*cur)->status == DQUOTE))
		{
			if (replace_var(cur,
					recover_val(*cur, (*cur)->str + i, data), i))
				return (1);
			continue ;
		}
		i++;
	}
	return (0);
}

char	*var_expander_heredoc(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == '$'
			&& !is_next_char_a_sep(str[i + 1])
			&& !var_between_quotes(str, i))
		{
			str = replace_str_heredoc(str,
					recover_val(NULL, str + i, data), i);
			continue ;
		}
		i++;
	}
	return (str);
}
