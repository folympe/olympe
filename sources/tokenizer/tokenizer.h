/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihaneasmoun <jiasmoun@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 16:18:39 by jihaneasmoun      #+#    #+#             */
/*   Updated: 2026/09/07 22:43:54 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

#include <stddef.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "libft.h"

# define QUOTE_ERROR "Error : Missing quote \n"
# define SPACE_TO_SKIP " \t"

typedef enum e_token_type
{
	TOKEN_OR,
	TOKEN_PIPE,
	TOKEN_HEREDOC,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_APPEND,
	TOKEN_REDIRECT_OUT,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_AND,
	TOKEN_WORD,
	TOKEN_NONE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	const char	*word;
	struct s_token	*next;
}	t_token;

# define TOKEN_STRINGS { \
	[TOKEN_OR]              = "||", \
	[TOKEN_PIPE]            = "|", \
	[TOKEN_HEREDOC]         = "<<", \
	[TOKEN_REDIRECT_IN]     = "<", \
	[TOKEN_REDIRECT_APPEND] = ">>", \
	[TOKEN_REDIRECT_OUT]    = ">",\
	[TOKEN_LPAREN]          = "(", \
	[TOKEN_RPAREN]          = ")", \
	[TOKEN_AND]             = "&&", \
	[TOKEN_WORD]            = NULL, \
}

t_token_type		get_token_type(const char *line);
int                     ft_strncmp(const char *s1, const char *s2, size_t n);
t_token			*tokenizer(const char *line);
bool			is_space_to_skip(char c);
char			*ft_strndup(const char *s1, size_t n);
t_token			*create_new_token(t_token_type type, const char *word);
void			add_back(t_token **token_list, t_token *token_new);
const char		*get_token_name(t_token_type type);
void			print_token_list(t_token *token_list);
int			skip_quote(const char *line);
char			*get_word(const char *line);

#endif

