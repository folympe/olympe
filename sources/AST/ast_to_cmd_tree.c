/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmd_tree.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 19:45:05 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 03:46:16 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_to_cmd.h"

static bool	convert_cmd(t_data *data, t_node *tree, t_command **head, t_command **last)
{
	t_command	*cmd;

	cmd = ast_new_cmd(tree);
	if (!cmd)
		return (false);
	if (!ast_fill_cmd(data, cmd, tree))
	{
		lst_clear_cmd(&cmd);
		return (false);
	}
	ast_add_cmd(head, last, cmd);
	return (true);
}

bool	ast_convert_tree(t_data *data, t_node *tree, t_command **head, t_command **last)
{
	t_command *left;

	if (!tree)
		return (true);
	if (!ast_is_operator(tree->type))
		return (convert_cmd(data, tree, head, last));
	if (!ast_convert_tree(data, tree->next, head, last))
		return (false);
	left = *last;
	if (!left)
		return (false);
	if (tree->type == TOKEN_PIPE)
		left->pipe_output = true;
	else
		left->next_op = tree->type;
	return (ast_convert_tree(data, tree->data.branch, head, last));
}

