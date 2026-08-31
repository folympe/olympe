/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/30 15:57:48 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/08/12 16:31:06 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	add_back_node(t_node *node_branch, t_node *node_new)
{
	while (node_branch->next)
		node_branch = node_branch->next;
	node_branch->next = node_new;
}
