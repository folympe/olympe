/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_fn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 22:26:37 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/05 16:10:13 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

static int	is_branch_type(t_node *node)
{
	return (node->type == TOKEN_PIPE
		|| node->type == TOKEN_OR
		|| node->type == TOKEN_AND);
}

static t_node	*create_word_node(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = TOKEN_WORD;
	node->data.word = token->word;
	node->next = NULL;
	return (node);
}

static t_node	*find_branch_node(t_node *node)
{
	while (is_branch_type(node) && node->data.branch)
		node = node->data.branch;
	return (node);
}

static int	add_word_node(t_token *token, t_node **tree)
{
	t_node	*node;
	t_node	*curr_node;

	node = create_word_node(token);
	if (!node)
		return (0);
	if (!*tree)
	{
		*tree = node;
		return (1);
	}
	curr_node = find_branch_node(*tree);
	if (is_branch_type(curr_node))
		curr_node->data.branch = node;
	else if (!add_back_node(curr_node, node, TOKEN_LPAREN))
	{
		free(node);
		return (0);
	}
	return (1);
}

t_ast_res	word_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;

	res.token = token->next;
	res.success = add_word_node(token, tree);
	res.tree = *tree;
	return (res);
}
