/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:27:03 by maamichaima       #+#    #+#             */
/*   Updated: 2024/06/07 16:00:08 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ignor(char *str)
{
	int		i;
	int		j;
	char	c;

	i = 0;
	j = 0;
	c = 0;
	while (str[i])
	{
		if (c == 0 && (str[i] == '\'' || str[i] == '\"'))
		{
			c = str[i++];
			continue ;
		}
		if (str[i] == c)
		{
			c = 0;
			i++;
		}
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	return (str);
}
