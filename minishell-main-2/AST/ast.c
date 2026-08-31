/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 16:01:24 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/08/12 16:32:36 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast_res       ast_builder(t_token *token, t_token_type end)
{
        t_builder_fn    tab[] = BUILDERS;
        t_ast_res       res;
        t_node          *tree;

        tree = NULL;
        while (token && token->type != end)
        {
                res = tab[token->type](token, &tree);
                if (res.success == false) //free tree
                        return (res);
                token = res.token;
        }
        return (res);
}