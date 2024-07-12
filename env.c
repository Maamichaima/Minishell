/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:58:47 by cmaami            #+#    #+#             */
/*   Updated: 2024/07/11 23:41:38 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcpy(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = s2[i];
	return (s1);
}

int	ft_lstsize(t_str *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**list_to_table(t_str *str)
{
	char	**t;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	t = ft_malloc(sizeof(char *) * (ft_lstsize(str) + 1), 'a');
	if (!t)
		return (NULL);
	while (str)
	{
		t[i] = ft_malloc(sizeof(char) * (ft_strlen(str->str) + 1), 'a');
		if (!t[i])
			return (NULL);
		t[i] = ft_strcpy(t[i], str->str);
		str = str->next;
		i++;
	}
	t[i] = NULL;
	return (t);
}

int	ft_lstsize_env(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**list_to_table_env(t_env *str)
{
	char	**t;
	int		i;

	i = 0;
	t = malloc(sizeof(char *) * (ft_lstsize_env(str) + 1));
	if (!t)
		return (NULL);
	while (str)
	{
		t[i] = ft_strjoin(str->key, "=");
		t[i] = ft_strjoin(t[i], str->value);
		str = str->next;
		i++;
	}
	t[i] = NULL;
	return (t);
}
