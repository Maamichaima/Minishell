/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 23:57:39 by rraida-           #+#    #+#             */
/*   Updated: 2024/06/07 16:13:58 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *src)
{
	size_t	i;
	size_t	l;
	char	*dest;

	l = ft_strlen(src);
	dest = malloc(sizeof(char) * (l + 1));
	if (dest == NULL)
		return (NULL);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
long	ft_atoi(char *str)
{
	int		i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		res *= 10;
		res = res + str[i] - '0';
		i++;
	}
	return (res * sign);
}

int	ft_isnum(int arg)
{
	if ((arg >= '0' && arg <= '9'))
		return (1);
	else
		return (0);
}

int	str_is_num(char *str)
{
	if (*str == '-' || *str == '+')
		str++;
	if (*str == '\0')
		return (1);
	while (*str)
	{
		if (!ft_isnum(*str))
			return (1);
		str++;
	}
	return (0);
}

int	is_builtin(t_str cmd)
{
	if (ft_strcmp(cmd.str, "cd") == 0 || ft_strcmp(cmd.str, "echo") == 0
		|| ft_strcmp(cmd.str, "pwd") == 0 || ft_strcmp(cmd.str, "export") == 0
		|| ft_strcmp(cmd.str, "unset") == 0 || ft_strcmp(cmd.str, "env") == 0
		|| ft_strcmp(cmd.str, "exit") == 0)
		return (1);
	return (0);
}