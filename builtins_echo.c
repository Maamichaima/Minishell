/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:05:56 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/10 17:40:04 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag[i] == '-' && flag[i])
	{
		i++;
		if (flag[i] == '\0')
			return (1);
		while (flag[i] && flag[i] == 'n')
		{
			i++;
		}
		if (flag[i] == '\0')
			return (0);
	}
	return (1);
}

int	ft_echo(char **args, int outfile)
{
	int	new_line;
	int	i;

	i = 0;
	if (args[1] == NULL)
	{
		write(outfile, "\n", 1);
		return (0);
	}
	new_line = 0;
	i++;
	while (args[i] && check_flag(args[i]) == 0)
	{
		i++;
		new_line = 1;
	}
	while (args[i])
	{
		write(outfile, args[i], ft_strlen(args[i]));
		if (args[i++])
			write(outfile, " ", 1);
	}
	if (new_line != 1)
		write(outfile, "\n", 1);
	return (0);
}
