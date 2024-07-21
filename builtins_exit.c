/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:05:13 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/20 22:08:53 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void write_error_exit(char **args, t_env *env , int x, int count)
{
	if(x == 1)
	{
		if(count == 1)
			write(2, "exit\n", 6);
	}
	else if(x == 2)
	{
		if(count == 1)
			write(2, "exit\n", 6);
		write(2, "bash: exit: ", 13);
		write(2, args[1], ft_strlen(args[1]));
		write(2, ": numeric argument required\n", 29);
		}

	else if(x == 3)
	{
		if(count == 1)
			write(2, "exit\n", 6);
	}
	clear_env(env);
	ft_malloc(0, 'f');
}


int	ft_exit(char **args, t_env *env, int count)
{
	int	e;

	if (args[0] && !args[1])
	{
		write_error_exit(args, env, 1, count);
		exit(0);
	}
	else if (str_is_num(args[1]) || (!str_is_num(args[1])
			&& ft_strlen(args[1]) > 12))
	{
		write_error_exit(args, env, 2, count);
		exit(255);
	}
	else if (args[0] && !str_is_num(args[1]) && args[2] == NULL)
	{
		e = ft_atoi(args[1]);
		write_error_exit(args, env, 3, count);
		exit(e);
	}
	else
	{
		if(count == 1)
			write(2, "exit\n", 6);
		write(2, "bash: exit: too many arguments\n", 32);
		return (1);
	}
	return (0);
}
