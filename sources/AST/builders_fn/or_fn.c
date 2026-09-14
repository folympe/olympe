/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   or_fn.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 22:26:12 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 15:05:06 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

t_ast_res	or_fn(t_token *token, t_node **tree)
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
	*node = (t_node){TOKEN_OR, {NULL}, NULL};
	res.success = true;
	res.token = token->next;
	if ((*tree)->type != TOKEN_OR && (*tree)->type != TOKEN_AND)
		return (node->next = *tree, *tree = node, res.tree = node, res);
	cur = *tree;
	while (cur->data.branch && (cur->data.branch->type == TOKEN_OR
			|| cur->data.branch->type == TOKEN_AND))
		cur = cur->data.branch;
	if (!cur->data.branch)
		return (free(node), res.success = false, res);
	node->next = cur->data.branch;
	cur->data.branch = node;
	return (res);
}
