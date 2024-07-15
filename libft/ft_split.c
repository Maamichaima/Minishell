/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:56:50 by cmaami            #+#    #+#             */
/*   Updated: 2024/07/15 00:45:48 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_quotes(char *str, int c, char h)
{
	int	lock;
	int	i;
	int	first;
	int	last;

	i = 0;
	lock = 0;
	while (str[i])
	{
		if (lock == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			lock = str[i];
			first = i;
		}
		else if (lock == str[i])
		{
			last = i;
			if (c < last && c > first)
				break ;
			lock = 0;
		}
		i++;
	}
	if (lock == '\"' || h == 'h')
		return (1);
	else if (lock == '\'')
		return (-1);
	else
		return (0);
}

int	is_separator(char *str, int a, char *charset)
{
	int	i;
	int	c;

	if (!str)
		return (0);
	c = str[a];
	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i] && !check_quotes(str, a, 0))
			return (1);
		i++;
	}
	return (0);
}

int	count_word(char *s, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && is_separator(s, i, c))
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '\0' && !is_separator(s, i, c))
			i++;
	}
	return (count);
}

int	c_char(char *s, char *c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && !is_separator(s, i, c))
		i++;
	return (i);
}

char	*alloc_word(char *s, char *c)
{
	int		i;
	char	*p;

	i = 0;
	p = ft_malloc(sizeof(char) * (c_char(s, c) + 1), 'a');
	if (!p)
		return (NULL);
	while (s[i] && !is_separator(s, i, c))
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	**ft_split(char *s, char *c)
{
	int		i;
	int		w;
	char	**tab;

	if (!s)
		return (NULL);
	i = 0;
	w = 0;
	tab = (char **)ft_malloc(sizeof(char *) * (count_word(s, c) + 1), 'a');
	if (!tab)
		return (NULL);
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && is_separator(s, i, c))
			i++;
		if (s[i] != '\0')
		{
			tab[w] = alloc_word(s + i, c);
			w++;
		}
		while (s[i] != '\0' && !is_separator(s, i, c))
			i++;
	}
	tab[w] = NULL;
	return (tab);
}
