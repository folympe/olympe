/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olfhal <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:41:19 by olfhal            #+#    #+#             */
/*   Updated: 2025/11/10 16:41:27 by olfhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static size_t	get_word_len(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	**free_all(char **new, size_t count)
{
	size_t	i;

	i = 0;
	while (i < count)
	{
		free(new[i]);
		i++;
	}
	free(new);
	return (NULL);
}

static char	**fill_words(char **new, const char *s, char c, size_t count)
{
	size_t	word;
	size_t	i;
	size_t	len;

	i = 0;
	word = 0;
	while (word < count)
	{
		while (s[i] == c)
			i++;
		len = get_word_len(s + i, c);
		new[word] = ft_substr(s, i, len);
		if (! new[word])
			return (free_all(new, word));
		while (s[i] && s[i] != c)
			i++;
		word++;
	}
	new[word] = NULL;
	return (new);
}

char	**ft_split(const char *s, char c)
{
	size_t	count;
	char	**new;

	if (s == NULL)
		return (NULL);
	count = count_words(s, c);
	new = malloc((count + 1) * sizeof(*new));
	if (new == NULL)
		return (NULL);
	return (fill_words(new, s, c, count));
}
