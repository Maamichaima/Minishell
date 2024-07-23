/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:08:31 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/22 15:49:29 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env *env)
{
	char	*str;

	(void)env;
	str = getcwd(NULL, 0);
	if (!str)
	{
		printf("%s\n", *path_secour());
		free(str);
		return (0);
	}
	printf("%s\n", str);
	free(str);
	return (0);
}
