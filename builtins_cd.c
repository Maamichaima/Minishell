/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:09:51 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/23 15:23:37 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**path_secour(void)
{
	static char	*p;

	return (&p);
}

void	error_cd(int a, char *str)
{
	if (a == 0)
	{
		write(2, "bash: cd:", 10);
		write(2, " HOME not set\n", 14);
	}
	else if (a == 2)
	{
		write(2, "bash: cd:", 10);
		write(2, " too many arguments\n", 21);
	}
	else
	{
		write(2, "bash: cd: ", 11);
		perror(str);
	}
}

int puts_err(char *val, char *old)
{
	if (!val)
	{
		(error_cd(0, val), free(old));
		return (1);
	}
	else if (chdir(val) == -1)
	{
		(error_cd(1, val), free(old));
		return (1);
	}
}

void set_old(char *new)
{
	if (new)
	{
		if (*path_secour())
			free(*path_secour());
		*path_secour() = ft_strdup(new);
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
	else if (args[1] && args[2])
	{
		(error_cd(2, val), free(old));
		return (1);
	}
	else if (args[1])
		val = args[1];
	if(puts_err(val, old))
		return (1);
	new = getcwd(NULL, 0);
	if (new)
		set_old(new);
	set_content(env, "PWD", new);
	set_content(env, "OLDPWD", old);
	return (0);
}
