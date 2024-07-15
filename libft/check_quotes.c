/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:45:37 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/15 21:45:59 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_quotes(char *str, int c, char h)
{
	int (lock), (i), (last), (first);
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
