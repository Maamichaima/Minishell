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

int	ft_echo(char **args, t_env *env)
{
	int	new_line;
	int	i;

	i = 0;
	if (args[1] == NULL)
	{
		printf("\n");
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
		printf("%s", args[i]);
		if (args[i++])
			printf(" ");
	}
	if (new_line != 1)
		printf("\n");
	return (0);
}
