/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 08:58:46 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 14:15:26 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	expand_args(t_data *data, t_command *cmd)
{
	char	*new_arg;
	int	i;

	i = 0;
	while (cmd->args && cmd->args[i])
	{
		new_arg = expand_word(data, cmd->args[i]);
		if (!new_arg)
			return (false);
		free_ptr(cmd->args[i]);
		cmd->args[i] = new_arg;
		i++;
	}
	cmd->command = cmd->args[0];
	return (true);
}

bool	expand_command_group(t_data *data, t_command *cmd)
{
	while (cmd)
	{
		if (!cmd->is_subshell && !expand_args(data, cmd))
			return (false);
		if (!prepare_command_redirs(data, cmd))
			return (false);
		cmd = cmd->next;
	}
	return (true);
}
