/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:04:34 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/10 17:07:18 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip(char *key, t_env **env, t_env **new)
{
	int	found;

	found = 0;
	if (ft_strcmp(get_key(key), (*new)->key) == 0)
	{
		if ((*new)->prev == NULL)
		{
			(*env) = (*env)->next;
			(*env)->prev = NULL;
		}
		else if (!(*new)->next)
		{
			(*new)->prev->next = NULL;
			found = 1;
		}
		else
		{
			(*new)->prev->next = (*new)->next;
			(*new)->next->prev = (*new)->prev;
		}
		found = 1;
	}
	return (found);
}

int	supp(char *key, t_env **env)
{
	t_env	*new;
	int		found;

	found = 0;
	new = *env;
	while (new)
	{
		found = skip(key, env, &new);
		new = new->next;
	}
	return (found);
}

int	ft_unset(char **args, t_env **env)
{
	t_env	*new;
	int		i;
	int		found;

	found = 0;
	new = *env;
	i = 0;
	if (!args[1])
		return (1);
	i++;
	while (args[i])
	{
		if (ft_strcmp(args[i], "_") != 0)
			found = supp(args[i], env);
		i++;
	}
	return (found);
}
