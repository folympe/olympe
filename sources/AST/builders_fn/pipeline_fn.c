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

static t_node	*find_pipe_pos(t_node *node)
{
	while (node->data.branch
		&& (node->data.branch->type == TOKEN_PIPE
			|| node->data.branch->type == TOKEN_OR
			|| node->data.branch->type == TOKEN_AND))
		node = node->data.branch;
	return (node);
}

t_ast_res	pipeline_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;
	t_node		*node;
	t_node		*cur;

	res = (t_ast_res){false, token, *tree};
	if (!*tree || !token->next || token->next->type == TOKEN_RPAREN)
		return (res);
	node = malloc(sizeof(t_node));
	if (!node)
		return (res);
	node->type = TOKEN_PIPE;
	node->data.branch = NULL;
	node->next = NULL;
	res.success = true;
	res.token = token->next;
	if (!((*tree)->type == TOKEN_PIPE || (*tree)->type == TOKEN_OR
			|| (*tree)->type == TOKEN_AND))
		return (node->next = *tree, *tree = node, res.tree = node, res);
	cur = find_pipe_pos(*tree);
	if (!cur->data.branch)
		return (free(node), res.success = false, res);
	node->next = cur->data.branch;
	cur->data.branch = node;
	return (res);
}
