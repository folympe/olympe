/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 23:28:56 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/06 05:31:58 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void  add_back(t_token **token_list, t_token *token_new)
{
        t_token *cur;
        //si la liste n existe pas
        if (!token_list || !token_new)
                return ;
        if (*token_list == NULL)
        {
                *token_list = token_new;
                return ;
        }
        //sinon on parcourt la lsite
        cur = *token_list;
        while (cur->next)
                cur = cur->next;
        //a la fin cur pointe sur le dernier maillon
        //on ajoute alors le nouveau maillon apres lui:
        cur->next = token_new;
}


t_token *create_new_token(t_token_type type, const char *word)
{
        t_token *new;

        new = (t_token*)malloc(sizeof(t_token));
        if (!new)
                return (NULL);
        new->type = type;
        new->word = word;
        new->next = NULL;
        return (new);
}

int     skip_quote(const char *line)
{
        int     i;
	char find_quote; 

	find_quote = *line;
        i = 1;
        while(line[i])
        {
                if (line[i] == find_quote)
                        return (i + 1);
                i++;
        }
        write(2, QUOTE_ERROR, ft_strlen(QUOTE_ERROR));
        return (-1);
}

bool is_space_to_skip(char c)
{
        int     i;
        char *spc_to_skip = SPACE_TO_SKIP;

        i = 0;
        while (spc_to_skip[i])
        {
                if (c == spc_to_skip[i])
                        return (true);
                i++;
        }
        return (false);
}

const char      *get_token_name(t_token_type type)
{
        if (type == TOKEN_OR)
                return ("TOKEN_OR");
        if (type == TOKEN_PIPE)
                return ("TOKEN_PIPE");
        if (type == TOKEN_HEREDOC)
                return ("TOKEN_HEREDOC");
        if (type == TOKEN_REDIRECT_IN)
                return ("TOKEN_REDIRECT_IN");
        if (type == TOKEN_REDIRECT_APPEND)
                return ("TOKEN_REDIRECT_APPEND");
        if (type == TOKEN_REDIRECT_OUT)
                return ("TOKEN_REDIRECT_OUT");
        if (type == TOKEN_LPAREN)
                return ("TOKEN_LPAREN");
        if (type == TOKEN_RPAREN)
                return ("TOKEN_RPAREN");
        if (type == TOKEN_AND)
                return ("TOKEN_AND");
        if (type == TOKEN_WORD)
                return ("TOKEN_WORD");
        return ("TOKEN_NONE");
}

