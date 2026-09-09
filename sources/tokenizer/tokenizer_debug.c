/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_debug.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/05 23:34:56 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/09/05 23:37:13 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

void	print_token_list(t_token *token_list)
{
	size_t	i;

	i = 0;
	while (token_list)
	{
		printf("maillon %zu : token_type : %s", i, get_token_name(token_list->type));
		if (token_list->word)
			printf(", word : %s", token_list->word);
		printf("\n");
		token_list = token_list->next;
		i++;
	}
}
