/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:16:22 by cmaami            #+#    #+#             */
/*   Updated: 2024/06/08 18:16:31 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize_(t_env *lst)
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

char	**table_of_key(t_env *env)
{
	char	**t;
	int		i;

	i = 0;
	t = malloc(sizeof(char *) * (ft_lstsize_(env) + 1));
	if (!t)
		return (NULL);
	while (env)
	{
		t[i] = env->key;
		env = env->next;
		i++;
	}
	t[i] = NULL;
	return (t);
}

char	**sort_table(char **str)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	while (str[i])
	{
		tmp = str[i];
		j = i - 1;
		while (j >= 0 && strcmp(str[j], tmp) > 0)
		{
			str[j + 1] = str[j];
			j--;
		}
		i++;
		str[j + 1] = tmp;
	}
	return (str);
}

char	*get_value_(char *key, t_env *env)
{
	while (env)
	{
		if (ft_strcmp(key, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_write_export(char **key, t_env *env)
{
	int	i;

	i = 0;
	while (key[i])
	{
		printf("declare -x %s", key[i]);
		if (get_value_(key[i], env))
			printf("=\"%s\"", get_value_(key[i], env));
		printf("\n");
		i++;
	}
}

// int main (int c, char **v)
// {
//     int i = 1;

//     sort_table(v+1);
//     printf("-----------------------------\n");
//     while(v[i])
//     {
//         printf("%s \n", v[i]);
//         i++;
//     }
//     return (0);
// }