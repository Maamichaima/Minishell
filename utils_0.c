/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.3>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:43:31 by rraida-           #+#    #+#             */
/*   Updated: 2024/07/06 23:30:11 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_content_f(t_env *env, char *key, char *content)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			free(env->value);
			env->value = content;
		}
		env = env->next;
	}
}

void	set_content(t_env *env, char *key, char *content)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			env->value = content;
		env = env->next;
	}
}

int	check_equal(char *str, int j)
{
	int	i;

	i = 0;
	if (str[0] == '=')
		return (0);
	while (str[i] && i < j)
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	copy(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	if (!src)
		return ;
	i = 0;
	j = ft_strlen(dst);
	while (src[i] != '\0')
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
}

int	len_get_expand_value(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isnum(str[i]) || str[i] == '_'))
		i++;
	return (i);
}