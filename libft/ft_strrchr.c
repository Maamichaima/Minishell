/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 11:23:10 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/18 11:06:35 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*ss;

	ss = (char *)s;
	i = ft_strlen(ss);
	while (i >= 0)
	{
		if (ss[i] == (char)c)
			return (ss + i);
		i--;
	}
	return (NULL);
}
