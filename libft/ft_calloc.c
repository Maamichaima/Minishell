/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:38:30 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/17 10:19:15 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;
	size_t	i;

	i = count * size;
	if (count != 0 && (i / count) != size)
		return (NULL);
	p = malloc(i);
	if (!p)
		return (NULL);
	ft_bzero(p, i);
	return (p);
}
