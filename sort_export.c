/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/08 18:16:22 by cmaami            #+#    #+#             */
/*   Updated: 2024/07/07 14:40:04 by maamichaima      ###   ########.fr       */
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
		printf("key  --> %s   \n", t[i]);
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
		// printf("%s   \n", str[i]);
		tmp = str[i];
		j = i - 1;
		while (j >= 0 && ft_strcmp(str[j], tmp) > 0)
		{
			str[j + 1] = str[j];
			j--;
		}
		i++;
		str[j + 1] = tmp;
	}
	printf("hhhhh\n");
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