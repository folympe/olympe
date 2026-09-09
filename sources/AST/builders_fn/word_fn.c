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

t_ast_res	word_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;
	t_node		*node;
	t_node		*curr_node;
	const int	mask = ((1 << TOKEN_PIPE) | (1 << TOKEN_OR) | (1 <<TOKEN_AND));

	res.token = token->next;
	res.success = true;
	node = (t_node *)malloc(sizeof(t_node));
	if (!node)
	{
		res.success = false;
		return (res);
	}
	node->type = TOKEN_WORD;
	node->data.word = token->word;
	node->next = NULL;
	if (!*tree)
	{
		*tree = node;
		res.tree = *tree;
		return (res);
	}
	curr_node = *tree;
	//faire un masque binaire
	while ((mask & (1 << curr_node->type)) && curr_node->data.branch)
		curr_node = curr_node->data.branch; //condition de parcours
	
	if (mask & (1 << curr_node->type))
		curr_node->data.branch = node;
	//si le curr_node est un pipe un or ou un and alors on ajoute le node dans la branche sinon on parcours le curr_node via next pour ajouter node a la fin;
	else if (!add_back_node(curr_node, node, TOKEN_LPAREN))
	{
		free(node);
		res.success = false;
	}
	res.tree = *tree;
	return (res);
}
