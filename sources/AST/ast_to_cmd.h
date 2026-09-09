/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_to_cmd.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 20:00:07 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 05:38:22 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_TO_CMD_H
#define AST_TO_CMD_H

#include "minishell.h"

bool	ast_is_operator(t_token_type);
int	ast_count_words(t_node *node);
t_command	*ast_new_cmd(t_node *node);;
void	ast_add_cmd(t_command **head,t_command **last, t_command *new_cmd);
bool	ast_fill_cmd(t_data *data, t_command *cmd, t_node *node);
bool	ast_add_redir(t_data *data, t_command *cmd, t_node *node);
bool	ast_convert_tree(t_data *data, t_node *tree, t_command **head, t_command **last);
bool	ast_to_commands(t_data *data, t_node *tree, t_command **commands);

#endif

