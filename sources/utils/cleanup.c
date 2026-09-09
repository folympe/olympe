/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 21:04:02 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 09:18:10 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_data(t_data *data, bool clear_history)
{
	if (data && data->user_input)
	{
		free_ptr(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		free_expand_token_list(&data->token);
	if (data && data->cmd)
		lst_clear_cmd(&data->cmd);
	if (clear_history && data)
	{
		free_ptr(data->working_dir);
		free_ptr(data->old_working_dir);
		free_str_tab(data->env);
		data->working_dir = NULL;
		data->old_working_dir = NULL;
		data->env = NULL;
		rl_clear_history();
	}
}

void	close_fds(t_command *cmds, bool close_backups)
{
	t_command	*cmd;

	cmd = cmds;
	while (cmd)
	{
		if (cmd->io_fds)
		{
			if (cmd->io_fds->fd_in != -1)
				close(cmd->io_fds->fd_in);
			if (cmd->io_fds->fd_out != -1)
				close(cmd->io_fds->fd_out);
			cmd->io_fds->fd_in = -1;
			cmd->io_fds->fd_out = -1;
			if (close_backups)
				restore_io(cmd->io_fds);
		}
		cmd = cmd->next;
	}
	close_pipe_fds(cmds, NULL);
}

void	free_io(t_io_fds *io)
{
	if (!io)
		return ;
	restore_io(io);
	if (io->fd_in != -1)
		close(io->fd_in);
	if (io->fd_out != -1)
		close(io->fd_out);
	if (io->heredoc_delimiter && io->infile)
		unlink(io->infile);
	free_ptr(io->heredoc_delimiter);
	free_ptr(io->infile);
	free_ptr(io->outfile);
	free_ptr(io);
}

void	free_str_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
		free_ptr(tab[i++]);
	free(tab);
}

void	free_ptr(void *ptr)
{
	if (ptr)
		free(ptr);
}
