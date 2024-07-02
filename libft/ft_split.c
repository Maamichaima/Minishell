/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:56:50 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/17 19:13:10 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	is_seperator(char s, char *c)
{
	int	i;

	i = 0;
	while (c[i])
	{
		if (c[i] == s)
			return (1);
		i++;
	}
	return (0);
}

int	count_word(char const *s, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && is_seperator(s[i], c))
			i++;
		if (s[i] != '\0')
			count++;
		while (s[i] != '\0' && !is_seperator(s[i], c))
			i++;
	}
	return (count);
}

int	c_char(const char *s, char *c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && !is_seperator(s[i], c))
		i++;
	return (i);
}

char	*alloc_word(const char *s, char *c)
{
	int		i;
	char	*p;

	i = 0;
	p = ft_malloc(sizeof(char) * (c_char(s, c) + 1), 'a');
	if (!p)
		return (NULL);
	while (s[i] && !is_seperator(s[i], c))
	{
		p[i] = s[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

void	*ft_free_split(int i, char **t)
{
	while (i > 0)
	{
		free(t[i - 1]);
		i--;
	}
	free(t);
	return (NULL);
}

char	**ft_split(char const *s, char *c)
{
	int		i;
	char	**tab;

	if (!s)
		return (NULL);
	i = 0;
	tab = (char **)ft_malloc(sizeof(char *) * (count_word(s, c) + 1), 'a');
	if (!tab)
		return (NULL);
	while (*s)
	{
		while (is_seperator(*s, c))
			s++;
		if (*s != '\0')
		{
			tab[i] = alloc_word(s, c);
			if (tab[i] == NULL)
				return (ft_free_split(i, tab));
			i++;
		}
		while (*s && !is_seperator(*s, c))
			s++;
	}
	tab[i] = NULL;
	return (tab);
}
