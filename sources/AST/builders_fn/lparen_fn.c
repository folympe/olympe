/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lparen_fn.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 15:24:41 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 05:42:00 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

t_ast_res	lparen_fn(t_token *token, t_node **tree)
{
	t_ast_res	branch_res;
	t_ast_res	res;
	t_node		*node;
	t_node		*curr_node;
	const int	mask = ((1 << TOKEN_PIPE) | (1 << TOKEN_OR) | (1 << TOKEN_AND));
	
	res.token = token;
	res.success = false;
	res.tree = *tree;
	branch_res = ast_builder(token->next, TOKEN_RPAREN);
	if (!branch_res.success || !branch_res.tree || !branch_res.token || branch_res.token->type != TOKEN_RPAREN)
		return (res);
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
		return (res);
	node->type = TOKEN_LPAREN;
	node->data.branch = branch_res.tree;
	node->next = NULL;
	res.token = branch_res.token->next;
	res.success = true;
	if (!*tree)
	{
		*tree = node;
		res.tree = *tree;
		return (res);
	}
	curr_node = *tree;
	while ((mask & (1 << curr_node->type)) && curr_node->data.branch)
		curr_node = curr_node->data.branch;
	if (mask & (1 << curr_node->type))
		curr_node->data.branch = node;
	else if (curr_node->type == TOKEN_LPAREN || !add_back_node(curr_node, node, TOKEN_WORD))
	{
		free(node);
		res.success = false;
	}
	res.tree = *tree;
	return (res);
}
