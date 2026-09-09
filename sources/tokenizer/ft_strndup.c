/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 19:11:20 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/07/25 16:42:42 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*p;
	size_t 	i;

	i = 0;
	while (s1[i] && i < n)
		i++;
	p = malloc(sizeof(char) * (i + 1));
	if (!p)
		return (NULL);
	i = 0;
	while (s1[i] && i < n)
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}
