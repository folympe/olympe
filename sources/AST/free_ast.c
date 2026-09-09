/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 18:49:19 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/05 18:51:39 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

void	free_ast(t_node *tree)
{
	if (!tree)
		return ;
	if (tree->type == TOKEN_PIPE || tree->type == TOKEN_AND || tree->type == TOKEN_OR || tree->type == TOKEN_LPAREN)
		free_ast(tree->data.branch);
	free_ast(tree->next);
	free(tree);
}
