/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:05:09 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/18 20:05:47 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	kayen(char const c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*alloc(char *p, int j, const char *debut)
{
	int	i;

	p = malloc(sizeof(char) * (j + 2));
	if (!p)
		return (NULL);
	i = 0;
	while (i <= j)
	{
		p[i] = debut[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int			i;
	char		*p;
	const char	*debut;
	const char	*fin;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	while (s1[i] && kayen(s1[i], set))
		i++;
	debut = &s1[i];
	if (*debut == '\0')
		return (ft_strdup(""));
	i = ft_strlen(s1) - 1;
	while (s1[i] && kayen(s1[i], set))
		i--;
	fin = &s1[i];
	i = fin - debut;
	p = NULL;
	p = alloc(p, i, debut);
	return (p);
}
