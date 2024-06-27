/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:38:54 by maamichaima       #+#    #+#             */
/*   Updated: 2024/06/15 15:28:18 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_whitespace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&') // || c == '(' || c == ')')
		return (1);
	return (0);
}

int	get_next_str_length(char *s, int i)
{
	int		len;
	char	lock;

	lock = 0;
	len = 0;
	while (s[i] && (lock || (!is_symbol(s[i]) && !is_whitespace(s[i]))))
	{
		if (!lock && (s[i] == '\'' || s[i] == '\"'))
			lock = s[i];
		else if (lock == s[i])
			lock = 0;
		i++;
		len++;
	}
	return (len);
}

char	*get_next_str(char *s, int *i)
{
	char	*token;
	int		j;
	char	lock;
	int		a;

	token = malloc(sizeof(char) * (get_next_str_length(s, *i) + 1));
	lock = 0;
	a = 0;
	j = 0;
	while (s[*i] && (lock || (!is_symbol(s[*i]) && !is_whitespace(s[*i]))))
	{
		if (!lock && (s[*i] == '\'' || s[*i] == '\"'))
		{
			lock = s[*i];
			a = *i;
		}
		token[j] = s[*i];
		if (lock == s[*i] && a != *i)
			lock = 0;
		(*i)++;
		j++;
	}
	token[j] = '\0';
	return (token);
}

char	*get_next_symbol(char *s, int *i)
{
	char	*token;
	int		j;

	token = malloc(3);
	j = 0;
	if (s[*i] && is_symbol(s[*i]))
	{
		token[j] = s[*i];
		(*i)++;
		j++;
	}
	if (s[*i] && (s[*i] == token[j - 1])) // && s[*i] != '(' && s[*i] != ')'))
	{
		token[j] = s[*i];
		(*i)++;
		j++;
	}
	token[j] = '\0';
	return (token);
}

char	*get_next_token(char *s)
{
	static int	i;

	while (s[i] && is_whitespace(s[i]))
		i++;
	if (!s[i])
	{
		i = 0;
		return (NULL);
	}
	if (!is_symbol(s[i]))
		return (get_next_str(s, &i));
	else
		return (get_next_symbol(s, &i));
}

void	print_token(char *s)
{
	char	*token;

	while (1)
	{
		token = get_next_token(s);
		if (!token)
			break ;
		puts(token);
	}
}
