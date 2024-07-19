/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:23:53 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/19 23:49:30 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctl_d(t_env *v)
{
	int	e;

	e = ft_atoi(get_value_("?", v));
	printf("exit\n");
	ft_malloc(0, 'f');
	clear_env(v);
	exit(e);
}

void	signal_handler(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, control_c);
}
