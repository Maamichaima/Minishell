/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:47:58 by rraida-           #+#    #+#             */
/*   Updated: 2024/06/07 17:12:58 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew_env(char *key, char *value, char *path)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->path = path;
	new->next = NULL;
	new->prev = NULL;
	// free(key);
	// free(value);
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
		new->prev = p;
	}
}

char	*get_key(char *env)
{
	int		i;
	char	*key;

	i = 0;
	key = malloc(256);
	while (env[i] && env[i] != '=' && env[i] != '+')
	{
		key[i] = env[i];
		i++;
	}
	key[i] = '\0';
	return (key);
}

char	*get_value(char *env)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	j = 0;
	while (env[i] && env[i] != '=')
	{
		i++;
	}
	if (env[i] == '\0')
		value = NULL;
	else
	{
		i++;
		value = ft_strdup(&env[i]);
	}
	return (value);
}

t_env	*get_env_lst(char **env)
{
	t_env	*new;
	t_env	*path;
	int		i;

	path = NULL;
	i = 0;
	while (env && env[i])
	{
		new = ft_lstnew_env(get_key(env[i]), getenv(get_key(env[i])), env[i]);
		ft_lstadd_back_env(&path, new);
		i++;
	}
	return (path);
}
