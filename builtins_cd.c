/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:09:51 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/17 20:01:38 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_cd(int a, char *str)
{
	if (a == 0)
	{
		write(2, "bash: cd:", 10);
		write(2, " HOME not set\n", 14);
	}
	else
	{
		write(2, "bash: cd: ", 11);
		perror(str);
	}
}

int	ft_cd(char **args, t_env *env)
{
	char	*old;
	char	*new;
	char	*val;

	old = getcwd(NULL, 0);
	if (args[1] == NULL)
		val = get_value_("HOME", env);
	else
		val = args[1];
	if (!val)
	{
		error_cd(0, val);
		return (1);
	}
	else if (chdir(val) == -1)
	{
		error_cd(1, val);
		return (1);
	}
	new = getcwd(NULL, 0);
	set_content(env, "PWD", new);
	set_content(env, "OLDPWD", old);
	return (0);
}
