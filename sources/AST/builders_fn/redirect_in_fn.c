/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_in_fn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 02:25:38 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/05 16:12:11 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

t_ast_res	redirect_in_fn(t_token *token, t_node **tree)
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
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
        {
                res.success = false;
                return (res);
        }
	node->type = TOKEN_REDIRECT_IN;
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
		add_back_node(curr_node, node, TOKEN_NONE);
	return (res);
}
