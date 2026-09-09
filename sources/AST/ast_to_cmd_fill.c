/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmd_fill.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 19:16:51 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 03:41:31 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_to_cmd.h"

static bool is_redirection(t_token_type type)
{
        return (type == TOKEN_REDIRECT_IN || type == TOKEN_REDIRECT_OUT || type == TOKEN_REDIRECT_APPEND || type == TOKEN_HEREDOC);
}

static bool fill_node(t_data *data, t_command *cmd, t_node *node, int *i)
{
	if (node->type == TOKEN_WORD)
	{
		cmd->args[*i] = ft_strdup((char *)node->data.word);
		if (!cmd->args[*i])
			return (false);
		(*i)++;
	}
	else if (is_redirection(node->type))
		return (ast_add_redir(data, cmd, node));
	else if (node->type == TOKEN_LPAREN)
	{
		cmd->is_subshell = true;
		return (ast_to_commands(data, node->data.branch, &cmd->subshell));
	}
	return (true);
}

bool	ast_fill_cmd(t_data *data, t_command *cmd, t_node *node)
{
	int	i;

	i = 0;
	while (node && !ast_is_operator(node->type))
	{
		if (!fill_node(data, cmd, node, &i))
			return (false);
		node = node->next;
	}
	if (!cmd->is_subshell)
		cmd->command = cmd->args[0];
	return (true);
}
