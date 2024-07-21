/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 01:05:18 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/15 18:26:37 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}

int	is_whitespace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int	is_symbol(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}
