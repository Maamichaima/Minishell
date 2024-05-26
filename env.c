/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:58:47 by cmaami            #+#    #+#             */
/*   Updated: 2024/05/25 18:58:51 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    *ft_strcpy(char *s1, char *s2)
{
    int i;

    i = 0;
    while (s2[i])
    {
        s1[i] = s2[i];
        i++;
    }
    s1[i] = s2[i];
    return (s1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
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

char **list_to_table(t_str *str)
{
    char **t;
    int i;

    i = 0;
    t = malloc(sizeof(char *) * (ft_lstsize(str) + 1));
    if(!t)
        return (NULL);
    while(str)
    {
        t[i] = malloc(sizeof(char) * (ft_strlen(str->str) + 1));
        if(!t[i])
            return (NULL);
        t[i] = ft_strcpy(t[i], str->str);
        str = str->next;
        i++;
    }
    t[i] = NULL;
    return (t);
}
