/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <cmaami@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 13:34:21 by cmaami            #+#    #+#             */
/*   Updated: 2023/11/17 10:17:45 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countnbr(int n)
{
	int	i;

	i = 1;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ch(long int n, char *t, int c)
{
	while (n > 0)
	{
		t[c] = n % 10 + '0';
		n = n / 10;
		c--;
	}
}

char	*ft_itoa(int nbr)
{
	long int	n;
	int			c;
	char		*t;

	n = nbr;
	c = countnbr(nbr);
	if (nbr < 0)
	{
		c++;
		n = -n;
	}
	t = ft_malloc(sizeof(char) * c + 1, 'a');
	if (!t)
		return (NULL);
	if (nbr < 0)
		t[0] = '-';
	if (nbr == 0)
		t[0] = '0';
	t[c] = '\0';
	c = c - 1;
	ch(n, t, c);
	return (t);
}
