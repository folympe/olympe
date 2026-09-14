/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 16:01:24 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/09 19:32:48 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

static t_ast_res	ast_error(t_token *token, t_node *tree)
{
	t_ast_res	res;

	res.success = false;
	res.token = token;
	res.tree = tree;
	return (res);
}

static void	init_builders(t_builder_fn *tab)
{
	int	i;

	i = 0;
	while (i <= TOKEN_WORD)
	{
		tab[i] = NULL;
		i++;
	}
	tab[TOKEN_OR] = or_fn;
	tab[TOKEN_PIPE] = pipeline_fn;
	tab[TOKEN_HEREDOC] = heredoc_fn;
	tab[TOKEN_WORD] = word_fn;
	tab[TOKEN_AND] = and_fn;
	tab[TOKEN_REDIRECT_IN] = redirect_in_fn;
	tab[TOKEN_REDIRECT_APPEND] = redirect_append_fn;
	tab[TOKEN_REDIRECT_OUT] = redirect_out_fn;
	tab[TOKEN_LPAREN] = lparen_fn;
}

t_ast_res	ast_builder(t_token *token, t_token_type end)
{
	t_builder_fn	tab[TOKEN_WORD + 1];
	t_ast_res		res;
	t_node			*tree;

	init_builders(tab);
	tree = NULL;
	res.success = true;
	while (token && token->type != end)
	{
		if (token->type > TOKEN_WORD || !tab[token->type])
			return (ast_error(token, tree));
		res = tab[token->type](token, &tree);
		if (res.success == false)
		{
			res.tree = tree;
			return (res);
		}
		token = res.token;
	}
	res.token = token;
	res.tree = tree;
	return (res);
}
