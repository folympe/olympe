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

static t_node	*find_branch(t_node *node)
{
	const int	mask = (1 << TOKEN_PIPE)
		| (1 << TOKEN_OR) | (1 << TOKEN_AND);

	while ((mask & (1 << node->type)) && node->data.branch)
		node = node->data.branch;
	return (node);
}

static int	add_lparen_node(t_node **tree, t_node *node)
{
	t_node	*curr;

	if (!*tree)
	{
		*tree = node;
		return (1);
	}
	curr = find_branch(*tree);
	if (curr->type == TOKEN_LPAREN)
		return (0);
	if (1 << curr->type & ((1 << TOKEN_PIPE)
			| (1 << TOKEN_OR) | (1 << TOKEN_AND)))
		curr->data.branch = node;
	else if (!add_back_node(curr, node, TOKEN_WORD))
		return (0);
	return (1);
}

static int	check_branch(t_ast_res branch)
{
	return (branch.success && branch.tree && branch.token
		&& branch.token->type == TOKEN_RPAREN);
}

static t_node	*new_lparen_node(t_node *branch)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = TOKEN_LPAREN;
	node->data.branch = branch;
	node->next = NULL;
	return (node);
}

t_ast_res	lparen_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;
	t_ast_res	branch;
	t_node		*node;

	res = (t_ast_res){token, false, *tree};
	branch = ast_builder(token->next, TOKEN_RPAREN);
	if (!check_branch(branch))
		return (res);
	node = new_lparen_node(branch.tree);
	if (!node || !add_lparen_node(tree, node))
	{
		free(node);
		return (res);
	}
	res.token = branch.token->next;
	res.tree = *tree;
	res.success = true;
	return (res);
}
