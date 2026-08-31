/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiasmoun <jiasmoun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 15:47:03 by jiasmoun          #+#    #+#             */
/*   Updated: 2026/08/12 16:03:04 by jiasmoun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tokenizer.h"

//Identifie l'operateur situe au debut de la chaine recue.

t_token_type	get_token_type(const char *line)
{
	t_token_type	type;
	const char	*token_strings[] = TOKEN_STRINGS;
	size_t	len;
	
	type = 0;
	while (type < TOKEN_WORD)
	{
		len = ft_strlen(token_strings[type]);
		if (ft_strncmp(line, token_strings[type], len) == 0)
		{
			return (type);
		}
		type++;
	}
	return (TOKEN_WORD);
}

//Fonction qui cree la liste de token

t_token	*tokenizer(const char *line)
{
	size_t	i;
	t_token *token_list;
	t_token *token_new;
	t_token_type	type;
	const char	*word;
	
	token_list = NULL;
	i = 0;
	while (line[i])
	{
		if (is_space_to_skip(line[i]))
		{
			i++;
			continue ;
		}
		type = get_token_type(line + i);
		word = NULL;
		if (type == TOKEN_WORD)
		{
			word = get_word(line + i);
			if (!word)
				return (NULL);//display error of malloc et free token_list
		i += ft_strlen(word);
		}
		else
			i += ft_strlen(((const char *[])TOKEN_STRINGS)[type]);
		token_new = create_new_token(type, word); // nouveau token avec le mot. 
		if (!token_new)
		{
			;//display error of malloc et free token_list
			return (NULL);
		}
		add_back(&token_list, token_new);
	//add_back (si ma liste est nulle ma liste est egale u nouveau maillon sinon parcourir ma liste et l ajouter apreds le nouveau maillon
	}
	return (token_list);
}

void	add_back(t_token **token_list, t_token *token_new)
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

int	skip_quote(const char *line)
{
	int	i;
	const char	find_quote = *line;
	
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

char	*get_word(const char *line)
{
	size_t	i;
	int	quote_info;
	
	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			quote_info = skip_quote(line + i);
			if (quote_info == -1)
				return (NULL);
			i += quote_info;
		}
		if (!line[i] || is_space_to_skip(line[i]) || get_token_type(line + i) != TOKEN_WORD)
			break ;
		else
			i++;
	}
	return (ft_strndup(line, i));
}

//on ne stocke pas les espaces. On avance dans la string pour trouver les tokens

bool is_space_to_skip(char c)
{
	int	i;
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

const char	*get_token_name(t_token_type type)
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

void	print_token_list(t_token *token_list)
{
	size_t	i;

	i = 1;
	while (token_list != NULL)
	{
		printf("maillon %zu : token_type : %s", i, get_token_name(token_list->type));
		if (token_list->word != NULL)
			printf(", word : %s", token_list->word);
		printf("\n");
		token_list = token_list->next;
		i++;
	}
}
