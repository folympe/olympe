/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/31 14:12:09 by olfhal            #+#    #+#             */
/*   Updated: 2026/08/31 14:12:12 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	restore_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	if (io->stdin_backup != -1 && dup2(io->stdin_backup, STDIN_FILENO) == -1)
		ret = false;
	if (io->stdin_backup != -1)
	{
		close(io->stdin_backup);
		io->stdin_backup = -1;
	}
	if (io->stdout_backup != -1 && dup2(io->stdout_backup, STDOUT_FILENO) == -1)
		ret = false;
	if (io->stdout_backup != -1)
	{
		close(io->stdout_backup);
		io->stdout_backup = -1;
	}
	return (ret);
}

bool	redirect_io(t_io_fds *io)
{
	int	ret;

	ret = true;
	if (!io)
		return (ret);
	io->stdin_backup = dup(STDIN_FILENO);
	if (io->stdin_backup == -1)
		ret = errmsg_cmd("dup", "stdin backup",
				strerror(errno), false);
	io->stdout_backup = dup(STDOUT_FILENO);
	if (io->stdout_backup == -1)
		ret = errmsg_cmd("dup", "stdout backup",
				strerror(errno), false);
	if (io->fd_in != -1 && dup2(io->fd_in, STDIN_FILENO) == -1)
		ret = errmsg_cmd("dup2", io->infile,
				strerror(errno), false);
	if (io->fd_out != -1 && dup2(io->fd_out, STDOUT_FILENO) == -1)
		ret = errmsg_cmd("dup2", io->outfile,
				strerror(errno), false);
	return (ret);
}

bool	check_infile_outfile(t_io_fds *io)
{
	if (!io)
		return (true);
	if (io->infile && io->fd_in == -1)
		return (false);
	if (io->outfile && io->fd_out == -1)
		return (false);
	return (true);
}
