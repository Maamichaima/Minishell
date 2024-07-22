/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:47:58 by rraida-           #+#    #+#             */
/*   Updated: 2024/07/21 22:11:59 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key_env(char *env)
{
	int		i;
	char	*key;

	i = 0;
	key = malloc(sizeof(char) * (ft_strlen(env) + 1));
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
	char	*value;

	i = 0;
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

void	add_default_env(t_env **path)
{
	t_env	*new;

	new = ft_lstnew_env(ft_strdup("PWD"), ft_strdup("/nfs/homes/rraida-/Desktop/mini"));
	ft_lstadd_back_env(path, new);
	new = ft_lstnew_env(ft_strdup("SHLVL"), ft_strdup("1"));
	ft_lstadd_back_env(path, new);
	new = ft_lstnew_env(ft_strdup("_"), ft_strdup("/usr/bin/env"));
	ft_lstadd_back_env(path, new);
	new = ft_lstnew_env(ft_strdup("PATH"), ft_strdup("/nfs/homes/rraida-/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin"));
	ft_lstadd_back_env(path, new);
	new= ft_lstnew_env(ft_strdup("?"),ft_strdup("0"));
	ft_lstadd_back_env(path, new);
}

t_env *get_new_node_in_env(char *env, char *key)
{
	int n;
	t_env *new;

	if(ft_strcmp(key, "SHLVL") == 0)
	{
		n = ft_atoi(getenv(key));
		n++;
		new = ft_lstnew_env(key, ft_itoa(n));
	}
	else
		new = ft_lstnew_env(key, ft_strdup(getenv(key)));
	return new;
}

t_env	*get_env_lst(char **env)
{
	t_env	*new;
	t_env	*path;
	int		i;
	char	*key;
	t_env	*x;

	path = NULL;
	i = 0;
	if (*env == NULL)
		add_default_env(&path);
	else
	{
		while (env && env[i])
		{
			key = get_key_env(env[i]);
			new = get_new_node_in_env(env[i], key);
			ft_lstadd_back_env(&path, new);
			i++;
		}
		key = ft_strdup("0");
		x = ft_lstnew_env(ft_strdup("?"), key);
		ft_lstadd_back_env(&path, x);
	}
	return (path);
}
