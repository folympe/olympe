/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 19:19:18 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/07/24 17:46:17 by jihaneasmoun     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <stdio.h>
//#include <string.h>
#include "tokenizer.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}
/*
int	main()
{
	printf("Expected : %zu, Got : %zu\n",strlen("ecole42"),ft_strlen("ecole42"));
	return (0);
}
*/
