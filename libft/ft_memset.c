/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 21:29:16 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/17 14:09:47 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	int				i;
	unsigned char	*p;

	p = b;
	i = 0;
	while (len > 0)
	{
		p[i] = (unsigned char)c;
		i++;
		len--;
	}
	return (b);
}
