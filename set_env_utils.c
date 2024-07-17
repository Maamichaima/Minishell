/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:23:39 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/17 18:01:40 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_lstadd_back_env(t_env **lst, t_env *new)
{
	t_env	*p;

	p = *lst;
	if (!lst || !new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	else
	{
		while (p->next != NULL)
			p = p->next;
		p->next = new;
		new->prev = p;
	}
}

char	*get_key(char *env)
{
	int		i;
	char	*key;

	i = 0;
	key = ft_malloc(sizeof(char) * (ft_strlen(env) + 1), 'a');
	while (env[i] && env[i] != '=' && env[i] != '+')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}
