/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 15:54:22 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/08/12 16:41:46 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "AST/ast.h"
#include <readline/readline.h>

int     main()
{
        // char s[] = "|";
        // char c = 'm';
        // printf("%d\n",get_token_type(s));
        // printf("%d\n",is_space_to_skip(c));
        // char    *line;
        // t_token *t_token_list;
        // line = "ls -a |     car -e| wc -l && ls | echo 'echec  | || && ou'aiiiii''";
        // t_token_list = tokenizer(line);
        // print_token_list(t_token_list);
        while (1)
        {
                char *line = readline("ceci est un prompt>");
                if (!line)
                        return 0;
                t_token *token_list = tokenizer(line);
                print_token_list(token_list);
                t_ast_res res = ast_builder(token_list, TOKEN_NONE);
                (void)res;
        }
        return (0);
}
