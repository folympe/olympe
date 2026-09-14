/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_out_fn.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihaneasmoun <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 03:53:51 by jihaneasmoun      #+#    #+#             */
/*   Updated: 2026/09/05 16:13:33 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

static int	is_branch_type(t_node *node)
{
	return (node->type == TOKEN_PIPE
		|| node->type == TOKEN_OR
		|| node->type == TOKEN_AND);
}

static t_node	*create_redirect_out_node(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = TOKEN_REDIRECT_OUT;
	node->data.word = token->next->word;
	node->next = NULL;
	return (node);
}

static t_node	*find_redirect_position(t_node *node)
{
	while (is_branch_type(node) && node->data.branch)
		node = node->data.branch;
	return (node);
}

static int	add_redirect_out(t_token *token, t_node **tree)
{
	t_node	*node;
	t_node	*curr_node;

	node = create_redirect_out_node(token);
	if (!node)
		return (0);
	if (!*tree)
	{
		*tree = node;
		return (1);
	}
	curr_node = find_redirect_position(*tree);
	if (is_branch_type(curr_node))
		curr_node->data.branch = node;
	else if (!add_back_node(curr_node, node, TOKEN_NONE))
	{
		free(node);
		return (0);
	}
	return (1);
}

t_ast_res	redirect_out_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;

	res.token = token->next;
	res.tree = *tree;
	res.success = false;
	if (!token->next || token->next->type != TOKEN_WORD)
		return (res);
	res.success = add_redirect_out(token, tree);
	res.tree = *tree;
	res.token = token->next->next;
	return (res);
}
