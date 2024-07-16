/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:08:06 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/16 19:48:46 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_key_in_env(t_env *env, char *args)
{
	int	i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(get_key(args), env->key) == 0)
		{
			while (args[i])
			{
				if (args[i] == '=' || args[i] == '+')
					break ;
				i++;
			}
			if (args[i] == '+' && args[i + 1] && args[i + 1] == '=')
				env->value = ft_strjoin(env->value, args + i + 2);
			else if (args[i] == '=')
			{
				if(env->value)
					free(env->value);
				env->value = ignor(get_value(args));
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

int	valide_key(char *str)
{
	if (str[0] == '_' || ft_isalpha(str[0]))
		return (1);
	return (0);
}

int	ft_error_export(char *str)
{
	write(2, "bash: export: ", 15);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 26);
	return (1);
}

int	ft_export(char **a, t_env *env)
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	i = 0;
	new = NULL;
	tmp = env;
	if (a[0] && !a[1])
		ft_write_export(sort_table(table_of_key(env)), env);
	else
	{
		i++;
		while (a[i])
		{
			if (valide_key(a[i]) == 0)
				return (ft_error_export(a[i]));
			else if (!check_key_in_env(env, a[i]))
			{
				new = ft_lstnew_env(get_key_env(a[i]), ignor(get_value(a[i])));
				ft_lstadd_back_env(&tmp, new);
			}
			i++;
		}
	}
	return (0);
}
