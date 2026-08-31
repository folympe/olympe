/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_fn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihaneasmoun <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 03:53:51 by jihaneasmoun      #+#    #+#             */
/*   Updated: 2026/08/12 16:37:57 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

t_ast_res	redirect_out_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;
	t_node		*node;
	t_node		*curr_node;
	const int	mask = ((1 << TOKEN_PIPE) | (1 << TOKEN_OR)
	| (1 << TOKEN_AND));
	res.success = true;
	res.token = token->next;
	res.tree = *tree;
	if (!token->next || token->next->type != TOKEN_WORD)
	{
		res.success = false;
		return (res);
	}
	node = malloc(sizeof(t_node));
	if (!node)
        {
                res.success = false;
                return (res);
        }
	node->type = TOKEN_REDIRECT_OUT;
	node->data.word = token->next->word;
	node->next = NULL;
	res.token = token->next->next;
	if (!*tree)
	{
		*tree = node;
		res.tree = *tree;
		return (res);
	}
	curr_node = *tree;
	while ((mask & (1 << curr_node->type))
	&& curr_node->data.branch != NULL)
		curr_node = curr_node->data.branch;
	if (mask & (1 << curr_node->type))
		curr_node->data.branch = node;
	else
		add_back_node(curr_node, node);
	return (res);
}
