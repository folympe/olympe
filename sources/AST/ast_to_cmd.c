/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 19:51:27 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 03:40:14 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast_to_cmd.h"

bool	ast_is_operator(t_token_type type)
{
	return (type == TOKEN_PIPE || type == TOKEN_AND || type == TOKEN_OR);
}

int	ast_count_words(t_node *node)
{
	int count;

	count = 0;
	while (node && !ast_is_operator(node->type))
	{
		if (node->type == TOKEN_WORD)
			count++;
		node = node->next;
	}
	return (count);
}

t_command	*ast_new_cmd(t_node *node)
{
	t_command	*cmd;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = ft_calloc(ast_count_words(node) + 1, sizeof(char *));
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->next_op = TOKEN_NONE;
	init_io(cmd);
	if (!cmd->io_fds)
	{
		free_str_tab(cmd->args);
		free(cmd);
		return (NULL);
	}
	return (cmd);
}

void	ast_add_cmd(t_command **head,  t_command **last, t_command *new_cmd)
{
	if (!*head)
		*head = new_cmd;
	else
	{
		(*last)->next = new_cmd;
		new_cmd->prev = *last;
	}
	*last = new_cmd;
}

bool	ast_to_commands(t_data *data, t_node *tree, t_command **commands)
{
	t_command	*last;

	*commands = NULL;
	last = NULL;
	if (!ast_convert_tree(data, tree, commands, &last))
	{
		lst_clear_cmd(commands);
		return (false);
	}
	return (true);
}
