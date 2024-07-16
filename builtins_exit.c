/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:05:13 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/16 20:04:53 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args)//free env 
{
	if (args[0] && !args[1])
	{
		write(2, "exit\n", 6);
		exit(0);
	}
	else if (str_is_num(args[1]) || (!str_is_num(args[1])
			&& ft_strlen(args[1]) > 12))
	{
		write(2, "exit\nbash: exit: ", 18);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 29);
		exit(255);
	}
	else if (args[0] && !str_is_num(args[1]) && args[2] == NULL)
	{
		write(2, "exit\n", 6);
		exit(ft_atoi(args[1]));
	}
	else
	{
		write(2, "exit\n", 6);
		write(2, "bash: exit: too many arguments\n", 32);
		return (1);
	}
	return (0);
}
