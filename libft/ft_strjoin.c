/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 14:00:13 by cmaami            #+#    #+#             */
/*   Updated: 2024/07/08 18:05:10 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		ls1;
	int		ls2;
	char	*p;

	if(!s1 && !s2)
		return NULL;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	p = malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (!p)
		return (NULL);
	p[0] = '\0';
	ft_strlcat(p, s1, ls1 + 1);
	ft_strlcat(p, s2, ls1 + ls2 + 1);
	return (p);
}
