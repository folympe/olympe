/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <olfhal@learner.42.tech>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/01 16:09:53 by olfhal            #+#    #+#             */
/*   Updated: 2026/09/07 21:31:45 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_out_of_range(int neg, unsigned long long num, int digit)
{
	unsigned long long limit;

	limit = (unsigned long long)LONG_MAX;
	if (neg == -1)
		limit++;
	return (num > (limit - digit) / 10);
}

static long ft_atoi_long(const char *str, bool *error)
{
	unsigned long long num;
	int		neg;
	int		i;
	int		digit;

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
	while (str[i] && ft_isdigit(str[i]))
	{
		digit = str[i++] - '0';
		if (check_out_of_range(neg, num, digit))
			return (*error = true, 0);
		num = num * 10 + digit;
	}
	if (neg == -1 && num == (unsigned long long)LONG_MAX + 1)
		return (LONG_MIN);
	return ((long)num * neg);
}

static int	get_exit_code(char *arg, bool *error)
{
	long	num;
	int	i;
	
	i = 0;
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (arg[i] == '+' || arg[i] == '-')
		i++;
	if (!ft_isdigit(arg[i]))
		*error = true;
	while (arg[i] && ft_isdigit(arg[i]))
		i++;
	while (arg[i] && ft_isspace(arg[i]))
		i++;
	if (arg[i])
		*error = true;
	num = ft_atoi_long(arg, error);
	if (*error)
		return (0);
	return ((int)((num % 256 + 256) % 256));
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
		exit_code = data->last_exit_code;
	exit_shell(data, exit_code);
	return (2);
}
