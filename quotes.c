/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 17:27:03 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/15 18:44:25 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ignor(char *str)
{
	t_ite	ite;
	char	c;

	inisialiser_ite(&ite);
	c = 0;
	if (!str)
		return (NULL);
	while (str[ite.i])
	{
		if (c == 0 && (str[ite.i] == '\'' || str[ite.i] == '\"'))
		{
			c = str[ite.i++];
			continue ;
		}
		if (str[ite.i] == c)
		{
			c = 0;
			ite.i++;
		}
		else
			str[ite.j++] = str[ite.i++];
	}
	str[ite.j] = '\0';
	return (str);
}

void	ignor_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return ;
	while (args[i])
	{
		ignor(args[i]);
		i++;
	}
}
