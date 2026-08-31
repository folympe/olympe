/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_fn.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/27 22:26:26 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/08/12 16:39:18 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ast.h"

t_ast_res	pipeline_fn(t_token *token, t_node **tree)
{
	t_ast_res	res;
	t_node		*node;
	t_node		*curr_node;
	const int	mask = ((1 << TOKEN_PIPE) | (1 << TOKEN_OR) | (1 << TOKEN_AND));

	if (!*tree)
	{
		res.success = false;
		return (res);
	}
	node = malloc(sizeof(t_node));
	res.success = true;
	res.token = token->next;
	res.tree = *tree;
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
	{	res.success = false;
		return (res);
	}
	node->next = curr_node->data.branch;
	curr_node->data.branch = node;
	return (res);
}
	//si l arbre commence par tout sauf ce qui est dans le masque on met la tete de larbre dans le next de pipe et pipe devient la tete de l arbre.
	//sinon on va parcourir l arbre tant que c est un noeud de type or and pipe onva boucler et tant ke la curr_node->dzta.branch->type correespond au mask on s arrete des que ca correspond plus
	//si y a un null c est qu il y a une erreur de syntaxe ex : | espace | 2token a la suite sans commande ntre les deux
	//dans notre branch on a une commande on va faire new_node->data.branch = curr_node ->data.branch 
	//et curr_node->data.branch = new_node
	//
