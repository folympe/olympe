/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_fn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 22:26:26 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 15:06:00 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

t_ast_res	pipeline_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;
	t_node		*node;
	t_node		*curr_node;
	const int	mask = ((1 << TOKEN_PIPE) | (1 << TOKEN_OR) | (1 << TOKEN_AND));

	res.success = false;
	res.token = token;
	res.tree = *tree;
	if (!*tree || !token->next || token->next->type == TOKEN_RPAREN)
		return (res);
	node = malloc(sizeof(t_node));
	res.success = true;
	res.token = token->next;
	if (!node)
	{
		res.success = false;
		return (res);
	}
	node->type = TOKEN_PIPE;
	node->data.branch = NULL;
	node->next = NULL;
	if (!(mask & (1 << (*tree)->type)))
	{
		node->next = *tree;
		*tree = node;
		res.tree = *tree;
		return (res);
	}
	curr_node = *tree;
	while (curr_node->data.branch && mask & (1 << (curr_node->data.branch->type)))
		curr_node = curr_node->data.branch; 
	if (!(curr_node->data.branch))
	{
		free(node);
		res.success = false;
		res.token = token;
		return (res);
	}
	node->next = curr_node->data.branch;
	curr_node->data.branch = node;
	return (res);
}
