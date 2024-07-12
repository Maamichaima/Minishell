/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:06:30 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/11 22:17:30 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env *env) // env (dhfbuhbshb || path)
{
	while (env)
	{
		if (env->value == NULL)
			(env) = (env)->next;
		else if (ft_strcmp("_", env->key) == 0)
			printf("%s=/usr/bin/env\n", env->key);
		else if (ft_strcmp("?", env->key) == 0)
		{
			(env) = (env)->next;
			continue ;
		}
		else
			printf("%s=%s\n", env->key, env->value);
		(env) = (env)->next;
	}
	return (0);
}
