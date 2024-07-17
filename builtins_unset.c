/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:04:34 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/17 22:30:29 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}

int skip(char *key, t_env **env, t_env *node)
{
    int found;
    t_env *prev_node;
    t_env *next_node;

	prev_node = node->prev;
	next_node = node->next;
	found  = 0;
    if (ft_strcmp(get_key(key), node->key) == 0)
    {
        if (prev_node == NULL)
        {
            *env = next_node;
            if (*env)
                (*env)->prev = NULL;
        }
        else
        {
            prev_node->next = next_node;
            if (next_node)
                next_node->prev = prev_node;
        }
        free_(node);
        found = 1;
    }
    return found;
}

int supp(char *key, t_env **env)
{
    t_env *current = *env;
    t_env *next_node;
    int found = 0;

    while (current)
    {
        next_node = current->next;
        if (skip(key, env, current))
            found = 1;
        current = next_node;
    }

    return found;
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	found;

	found = 0;
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
