/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:06:30 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/19 22:51:28 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env)
{
	while (env)
	{
		if (ft_strcmp("_", env->key) == 0)
			printf("%s=/usr/bin/env\n", env->key);
		else if (ft_strcmp("?", env->key) == 0)
		{
			(env) = (env)->next;
			continue ;
		}
		else
		{
			if (env->value && env->key)
				printf("%s=%s\n", env->key, env->value);
		}
		(env) = (env)->next;
	}
	return (0);
}
