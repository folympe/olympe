/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 08:53:24 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 14:16:19 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	expand_quotes(t_data *data, t_expand_token *token)
{
	t_expand_token	*old_token;
	bool		failed;

	token->status = DEFAULT;
	old_token = data->token;
	data->token = token;
	failed = (handle_quotes(data) != 0);
	data->token = old_token;
	return (!failed);
}

char	*expand_word(t_data *data, const char *word)
{
	t_expand_token	token;
	t_expand_token	*current;
	
	current = &token;
	ft_memset(&token, 0, sizeof(token));
	token.str = ft_strdup((char *)word);
	if (!token.str)
		return (NULL);
	if (expand_token_word(data, &current) || !expand_quotes(data, &token))
	{
		free_ptr(token.str);
		return (NULL);
	}
	return (token.str);
}
