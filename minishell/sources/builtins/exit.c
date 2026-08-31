/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:09:53 by olfhal            #+#    #+#             */
/*   Updated: 2026/07/01 16:09:56 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_out_of_range(int neg, unsigned long long num, bool *error)
{
	if (!*error)
	{
		if (neg == 1)
		{
			if (num > LONG_MAX)
				*error = true;
		}
		else
		{
			if (num > -(unsigned long)LONG_MIN)
				*error = true;
		}
	}
	return (*error);
}

static int	ft_atoi_long(const char *str, bool *error)
{
	unsigned long long	num;
	int					neg;
	int					i;

	num = 0;
	neg = 1;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			neg = -1;
		i++;
	}
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			break ;
		num = num * 10 + (str[i] - '0');
		if (check_out_of_range(neg, num, error))
			break ;
		i++;
	}
	return ((int)(num * neg));
}

static int	get_exit_code(char *arg, bool *error)
{
	unsigned long long	i;

	if (!arg)
		return (g_last_exit_code);
	i = 0;
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (!arg[i])
		*error = true;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (arg[i] && !ft_isdigit(arg[i]))
		*error = true;
	while (arg[i])
	{
		if (ft_isspace(arg[i]) == 0 && !ft_isdigit(arg[i]))
			*error = true;
		i++;
	}
	i = ft_atoi_long(arg, error);
	return ((int)(i % 256));
}

static bool	is_quiet_mode(t_data *data)
{
	t_command	*cmd;

	cmd = data->cmd;
	if (cmd == NULL)
		return (false);
	return (cmd->next || cmd->prev);
}

int	exit_builtin(t_data *data, char **args)
{
	int		exit_code;
	bool	error;
	bool	quiet;

	error = false;
	quiet = is_quiet_mode(data);
	if (data->interactive && !quiet)
		ft_putendl_fd("exit", 2);
	if (args && args[1])
	{
		exit_code = get_exit_code(args[1], &error);
		if (error)
			exit_code = errmsg_cmd("exit", args[1],
					"numeric argument required", 2);
		else if (args[2])
			return (errmsg_cmd("exit", NULL, "too many arguments", 1));
	}
	else
		exit_code = g_last_exit_code;
	exit_shell(data, exit_code);
	return (2);
}
