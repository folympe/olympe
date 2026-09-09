/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/12 16:01:24 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/05 18:56:26 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ast.h"

t_ast_res       ast_builder(t_token *token, t_token_type end)
{
        t_builder_fn    tab[] = BUILDERS;
        t_ast_res       res;
        t_node          *tree;

        tree = NULL;
        res.success = true;
	while (token && token->type != end)
        {
		if (token->type > TOKEN_WORD || !tab[token->type])
		{
			res.success = false;
			res.token = token;
			res.tree = tree;
			return (res);
		}
                res = tab[token->type](token, &tree);
                if (res.success == false)
		{
			res.tree = tree;
                        return (res);
		}
                token = res.token;
        }
	res.token = token;
	res.tree = tree;
        return (res);
}
