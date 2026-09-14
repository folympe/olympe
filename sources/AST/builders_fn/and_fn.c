/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_fn.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 22:26:12 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 15:03:55 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

static t_node	*new_and_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = TOKEN_AND;
	node->data.branch = NULL;
	node->next = NULL;
	return (node);
}

static int	insert_and(t_node **tree, t_node *node)
{
	t_node		*curr;
	const int	mask = (1 << TOKEN_OR) | (1 << TOKEN_AND);

	if (!(mask & (1 << (*tree)->type)))
	{
		node->next = *tree;
		*tree = node;
		return (1);
	}
	curr = *tree;
	while (curr->data.branch
		&& (mask & (1 << curr->data.branch->type)))
		curr = curr->data.branch;
	if (!curr->data.branch)
		return (0);
	node->next = curr->data.branch;
	curr->data.branch = node;
	return (1);
}

t_ast_res	and_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;
	t_node		*node;

	res.success = false;
	res.token = token;
	res.tree = *tree;
	if (!*tree || !token->next || token->next->type == TOKEN_RPAREN)
		return (res);
	node = new_and_node();
	if (!node || !insert_and(tree, node))
	{
		free(node);
		return (res);
	}
	res.success = true;
	res.token = token->next;
	res.tree = *tree;
	return (res);
}
