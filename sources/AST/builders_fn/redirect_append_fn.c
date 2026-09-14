/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append_fn.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihaneasmoun <marvin@42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/10 03:45:53 by jihaneasmoun      #+#    #+#             */
/*   Updated: 2026/09/05 16:15:03 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

static bool	valid_append(t_token *token)
{
	return (token->next && token->next->type == TOKEN_WORD);
}

static t_node	*new_append(t_token *token)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = TOKEN_REDIRECT_APPEND;
	node->data.word = token->next->word;
	node->next = NULL;
	return (node);
}

static void	add_append(t_node **tree, t_node *node)
{
	t_node		*curr;
	const int	mask = (1 << TOKEN_PIPE) | (1 << TOKEN_OR)
		| (1 << TOKEN_AND);

	if (!*tree)
	{
		*tree = node;
		return ;
	}
	curr = *tree;
	while ((mask & (1 << curr->type)) && curr->data.branch)
		curr = curr->data.branch;
	if (mask & (1 << curr->type))
		curr->data.branch = node;
	else
		add_back_node(curr, node, TOKEN_NONE);
}

t_ast_res	redirect_append_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;
	t_node		*node;

	res.success = false;
	res.token = token->next;
	res.tree = *tree;
	if (!valid_append(token))
		return (res);
	node = new_append(token);
	if (!node)
		return (res);
	res.token = token->next->next;
	add_append(tree, node);
	res.tree = *tree;
	res.success = true;
	return (res);
}
