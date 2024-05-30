/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:47:58 by rraida-           #+#    #+#             */
/*   Updated: 2024/05/28 19:40:33 by maamichaima      ###   ########.fr       */
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
	// free(key);
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
		{
			p = p->next;
		}
		p->next = new;
	}
}

char	*get_key(char *env)
{
	int		i;
	char	*key;

	key = malloc(256);
	i = 0;
	while (env && env[i] != '=')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

t_env	*get_env_lst(char **env)
{
	t_env *new;
	t_env *path;
	int i;

	path = NULL;
	i = 0;
	while (env && env[i])
	{
		new = ft_lstnew_env(get_key(env[i]), getenv(get_key(env[i])));
		ft_lstadd_back_env(&path, new);
		i++;
	}
	return (path);
}
