/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 23:51:36 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 09:38:00 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include <signal.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>

extern volatile sig_atomic_t	g_signal;

void	set_dad_signals(void);
void	set_son_signals(void);
void	set_heredoc_signals(void);

#endif
