/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:05:40 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/19 14:42:39 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*p;
	size_t	j;
	size_t	i;

	if (!s)
		return (NULL);
	j = 0;
	i = 0;
	if (ft_strlen(s) <= start)
		len = 0;
	else if (len >= (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	p = malloc(sizeof(char) * (len + 1));
	if (!p)
		return (NULL);
	while (s[i] != '\0')
	{
		if (i >= start && j < len)
		{
			p[j++] = s[i];
		}
		i++;
	}
	p[j] = '\0';
	return (p);
}
