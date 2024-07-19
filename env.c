/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:58:47 by cmaami            #+#    #+#             */
/*   Updated: 2024/07/17 15:52:27 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_strjoin_(char *s1, char *s2)
{
	int		ls1;
	int		ls2;
	char	*p;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	p = ft_malloc(sizeof(char) * (ls1 + ls2 + 2), 'a');
	if (!p)
		return (NULL);
	p[0] = '\0';
	ft_strlcat(p, s1, ls1 + 1);
	ft_strlcat(p, "=", ls1 + 2);
	ft_strlcat(p, s2, ls1 + ls2 + 2);
	// free(s1);
	return (p);
}

char	**list_to_table_env(t_env *str)
{
	char	**t;
	int		i;

	i = 0;
	t = ft_malloc(sizeof(char *) * (ft_lstsize_env(str) + 1), 'a');
	if (!t)
		return (NULL);
	while (str)
	{
		// if (str->key[0] == '?')
		// {
		// 	str = str->next;
		// 	continue ;
		// }
		t[i] = ft_strjoin_(str->key, str->value);
		str = str->next;
		i++;
	}
	t[i] = NULL;
	return (t);
}
