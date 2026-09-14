/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@learner.42.tech>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 20:16:55 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/11 20:17:01 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

static void	clear_tokenizer(t_token **tokens)
{
	t_token	*next;

	while (tokens && *tokens)
	{
		next = (*tokens)->next;
		free((void *)(*tokens)->word);
		free(*tokens);
		*tokens = next;
	}
}

t_token_type	get_token_type(const char *line)
{
	if (ft_strncmp(line, "||", 2) == 0)
		return (TOKEN_OR);
	if (ft_strncmp(line, "|", 1) == 0)
		return (TOKEN_PIPE);
	if (ft_strncmp(line, "<<", 2) == 0)
		return (TOKEN_HEREDOC);
	if (ft_strncmp(line, "<", 1) == 0)
		return (TOKEN_REDIRECT_IN);
	if (ft_strncmp(line, ">>", 2) == 0)
		return (TOKEN_REDIRECT_APPEND);
	if (ft_strncmp(line, ">", 1) == 0)
		return (TOKEN_REDIRECT_OUT);
	if (ft_strncmp(line, "(", 1) == 0)
		return (TOKEN_LPAREN);
	if (ft_strncmp(line, ")", 1) == 0)
		return (TOKEN_RPAREN);
	if (ft_strncmp(line, "&&", 2) == 0)
		return (TOKEN_AND);
	return (TOKEN_WORD);
}

static bool	tokenize_one(const char *line, size_t *i, t_token **list)
{
	t_token_type	type;
	const char		*word;
	t_token			*new;

	type = get_token_type(line + *i);
	word = NULL;
	if (type == TOKEN_WORD)
	{
		word = get_word(line + *i);
		if (!word)
			return (false);
		*i += ft_strlen(word);
	}
	else if (type == TOKEN_OR || type == TOKEN_HEREDOC
		|| type == TOKEN_REDIRECT_APPEND || type == TOKEN_AND)
		*i += 2;
	else
		*i += 1;
	new = create_new_token(type, word);
	if (!new)
		return (free((void *)word), false);
	add_back(list, new);
	return (true);
}

t_token	*tokenizer(const char *line)
{
	size_t	i;
	t_token	*list;

	list = NULL;
	i = 0;
	while (line[i])
	{
		if (is_space_to_skip(line[i]))
			i++;
		else if (!tokenize_one(line, &i, &list))
		{
			clear_tokenizer(&list);
			return (NULL);
		}
	}
	return (list);
}

char	*get_word(const char *line)
{
	size_t	i;
	int		quote_info;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			quote_info = skip_quote(line + i);
			if (quote_info == -1)
				return (NULL);
			i += quote_info;
			continue ;
		}
		if (!line[i] || is_space_to_skip(line[i])
			|| get_token_type(line + i) != TOKEN_WORD)
			break ;
		else
			i++;
	}
	return (ft_strndup(line, i));
}
