/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 13:48:12 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/18 11:06:24 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*s;
	char	*f;

	s = (char *)haystack;
	f = (char *)needle;
	i = 0;
	if (f[0] == '\0')
		return (s);
	while (s[i] != '\0' && i < len)
	{
		j = 0;
		while (s[i + j] != '\0' && s[i + j] == f[j] && i + j < len)
		{
			if (f[j + 1] == '\0')
				return (&s[i]);
			j++;
		}
		i++;
	}
	return (0);
}
