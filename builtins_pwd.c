/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_pwd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:08:31 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/17 20:04:31 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_env *env)
{
	(void)env;
	char *str;
	
	str = getcwd(NULL, 0);
	printf("%s\n", str);
	free(str);
	return (0);
}
