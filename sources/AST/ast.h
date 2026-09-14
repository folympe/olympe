/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 16:05:24 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/09 19:33:56 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AST_H
# define AST_H
# include <stddef.h>
# include <stdbool.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include "../tokenizer/tokenizer.h"

typedef union u_ast_data
{
	const char		*word;
	int				fd;
	struct s_node	*branch;
}	t_ast_data;

typedef struct s_node
{
	t_token_type	type;
	t_ast_data		data;
	struct s_node	*next;
}	t_node;

typedef struct s_ast_res
{
	t_token	*token;
	bool	success;
	t_node	*tree;
}	t_ast_res;

typedef t_ast_res(*	t_builder_fn)(t_token *token, t_node **node);

t_ast_res		ast_builder(t_token *token, t_token_type end);
bool			add_back_node(t_node *node_branch, t_node *node_new,
					t_token_type forbidden);	
void			free_ast(t_node *tree);
t_ast_res		or_fn(t_token *token, t_node **tree);
t_ast_res		pipeline_fn(t_token *token, t_node **tree);
t_ast_res		heredoc_fn(t_token *token, t_node **tree);
t_ast_res		word_fn(t_token *token, t_node **tree);
t_ast_res		and_fn(t_token *token, t_node **tree);
t_ast_res		redirect_in_fn(t_token *token, t_node **tree);
t_ast_res		redirect_append_fn(t_token *token, t_node **tree);
t_ast_res		redirect_out_fn(t_token *token, t_node **tree);
t_ast_res		lparen_fn(t_token *token, t_node **tree);

#endif
