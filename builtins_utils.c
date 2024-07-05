/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 23:57:39 by rraida-           #+#    #+#             */
/*   Updated: 2024/06/15 16:27:26 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isnum(int arg)
{
	if ((arg >= '0' && arg <= '9'))
		return (1);
	else
		return (0);
}

int	str_is_num(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (!ft_isnum(*str))
			return (1);
		str++;
	}
	return (0);
}

int	is_builtin(t_str cmd)
{
	if (ft_strcmp(cmd.str, "cd") == 0 || ft_strcmp(cmd.str, "echo") == 0
		|| ft_strcmp(cmd.str, "pwd") == 0 || ft_strcmp(cmd.str, "export") == 0
		|| ft_strcmp(cmd.str, "unset") == 0 || ft_strcmp(cmd.str, "env") == 0
		|| ft_strcmp(cmd.str, "exit") == 0)
		return (1);
	return (0);
}
