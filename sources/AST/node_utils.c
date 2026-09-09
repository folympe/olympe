/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:57:48 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/05 15:21:10 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

bool	add_back_node(t_node *node_branch, t_node *node_new, t_token_type forbidden)
{
	t_node	*curr;

	curr = node_branch;
	while (curr)
	{
		if (curr->type == forbidden)
			return (false);
		if (!curr->next)
			break ;
		curr = curr->next;
	}
	curr->next = node_new;
	return (true);
}
