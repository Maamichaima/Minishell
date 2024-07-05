/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:59:35 by rraida-           #+#    #+#             */
/*   Updated: 2024/06/07 23:03:35 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_env *env)
{
	char	**paths;

	while (env)
	{
		if (ft_strcmp(env->key, "PATH") == 0)
		{
			paths = ft_split(env->value, ":");
		}
		env = env->next;
	}
	return (paths);
}

char	*ft_strjoin_pipe(char *s1, char *s2)
{
	int		i;
	int		j;
	char	lg;
	char	*str;

	lg = ft_strlen(s1) + ft_strlen(s2) + 2;
	i = 0;
	j = 0;
	str = (char *)ft_malloc(lg * sizeof(char), 'a');
	if (str == NULL)
		return (0);
	while (s1[i])
	{
		str[j++] = s1[i++];
	}
	str[j] = '/';
	j++;
	i = 0;
	while (s2[i])
		str[j++] = s2[i++];
	str[j] = '\0';
	return (str);
}

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != (char)c)
		s++;
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*correct_path(char **path, char *v)
{
	char	*tmp;
	int		i;

	i = 0;
	if (!v)
		return (NULL);
	if (ft_strchr(v, '/') || !path)
		return (v);
	while (path && path[i])
	{
		tmp = ft_strjoin_pipe(path[i], v);
		if (access(tmp, F_OK | X_OK) == -1)
		{
			free(tmp);
			i++;
		}
		else if (access(tmp, F_OK | X_OK) == 0)
			return (tmp);
	}
	return (NULL);
}
