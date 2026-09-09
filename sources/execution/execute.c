/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/06 09:08:13 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 09:11:10 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command	*get_group_end(t_command *start)
{
	t_command	*end;
	
	end = start;
	while (end->next && end->next_op != TOKEN_AND && end->next_op != TOKEN_OR)
		end = end->next;
	return (end);
}

static bool	should_run(t_token_type op, int status)
{
	if (op == TOKEN_NONE)
		return (true);
	if (op == TOKEN_AND && 	status == 0)
		return (true);
	if (op == TOKEN_OR && status != 0)
		return (true);
	return (false);
}

static int	run_group(t_data *data, t_command *start, t_command *end)
{
	t_command	*all;
	t_command	*next;
	t_command	*old_prev;
	int		status;

	all = data->cmd;
	next = end->next;
	old_prev = start->prev;
	end->next = NULL;
	start->prev = NULL;
	if (next)
		next->prev = NULL;
	data->cmd = start;
	status = 1;
	if (expand_command_group(data, start))
		status = execute_pipeline(data);
	data->cmd = all;
	start->prev = old_prev;
	end->next = next;
	if (next)
		next->prev = end;
	return (status);
}

int	execute(t_data *data)
{
	t_command	*start;
	t_command	*end;
	t_token_type	previous_op;
	int		status;

	start = data->cmd;
	status = data->last_exit_code;
	previous_op = TOKEN_NONE;
	while (start)
	{
		end = get_group_end(start);
		if (should_run(previous_op, status))
		{
			data->last_exit_code = status;
			status = run_group(data, start, end);
		}
		previous_op = end->next_op;
		start = end->next;
	}
	data->last_exit_code = status;
	return (status);
}
