/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_fn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 16:25:50 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 03:25:08 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

static t_node	*new_heredoc_node(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = TOKEN_HEREDOC;
	node->data.word = token->word;
	node->next = NULL;
	return (node);
}

static int	add_heredoc_node(t_node **tree, t_node *node)
{
	t_node		*curr;
	const int	mask = (1 << TOKEN_PIPE)
		| (1 << TOKEN_OR) | (1 << TOKEN_AND);

	if (!*tree)
	{
		*tree = node;
		return (1);
	}
	curr = *tree;
	while ((mask & (1 << curr->type)) && curr->data.branch)
		curr = curr->data.branch;
	if (mask & (1 << curr->type))
		curr->data.branch = node;
	else if (!add_back_node(curr, node, TOKEN_NONE))
		return (0);
	return (1);
}

t_ast_res	heredoc_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;
	t_node		*node;

	res.success = false;
	res.token = token->next;
	res.tree = *tree;
	if (!token->next || token->next->type != TOKEN_WORD)
		return (res);
	node = new_heredoc_node(token->next);
	if (!node || !add_heredoc_node(tree, node))
	{
		free(node);
		return (res);
	}
	res.token = token->next->next;
	res.tree = *tree;
	res.success = true;
	return (res);
}
