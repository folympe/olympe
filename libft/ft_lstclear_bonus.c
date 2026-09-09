/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/14 14:21:12 by olfhal            #+#    #+#             */
/*   Updated: 2025/11/14 14:21:13 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*elem;
	t_list	*next;

	if (lst == NULL || del == NULL)
		return ;
	elem = *lst;
	while (elem)
	{
		next = elem->next;
		ft_lstdelone(elem, del);
		elem = next;
	}
	*lst = NULL;
}
