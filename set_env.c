/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:47:58 by rraida-           #+#    #+#             */
/*   Updated: 2024/07/12 12:32:02 by rraida-          ###   ########.fr       */
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
		{
			p = p->next;
		}
		p->next = new;
		new->prev = p;
	}
}
// thydat 256
char	*get_key(char *env)
{
	int		i;
	char	*key;

	i = 0;
	key = malloc(sizeof(char) * ft_strlen(env + 1));
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
	if (*env == NULL)
	{
		new = ft_lstnew_env("PWD","/nfs/homes/rraida-/Desktop/mini");
		ft_lstadd_back_env(&path, new);
		new = ft_lstnew_env("SHLVL","1");
		ft_lstadd_back_env(&path, new);
		new = ft_lstnew_env("_", "/usr/bin/env");
		ft_lstadd_back_env(&path, new);
	}
	else
	{		
		while (env && env[i])
			{
				new = ft_lstnew_env(get_key(env[i]), getenv(get_key(env[i])));
				ft_lstadd_back_env(&path, new);
				i++;
			}
			ft_lstadd_back_env(&path, ft_lstnew_env("?", ft_strdup("0")));
	}
	return (path);
}
