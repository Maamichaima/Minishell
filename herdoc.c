/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:34:31 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/24 13:17:59 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fd_here_doc(t_str *red, t_env *env)
{
	int	status;

	while (red)
	{
		if (red->type == token_herd)
		{
			red->fd = open_here_doc(red->str, env);
			wait(&status);
			if (status)
				return (0);
		}
		red = red->next;
	}
	return (1);
}

int	execut_all_here_doc(t_ast *root, t_env *env)
{
	int	i;

	i = 1;
	if (root->type == token_cmd)
		return (fd_here_doc(root->red, env));
	else
	{
		i = execut_all_here_doc(root->left, env);
		if (i)
			i = execut_all_here_doc(root->right, env);
	}
	return (i);
}

int	get_last_fd(t_str *red, char c)
{
	int	f;

	while (red)
	{
		if (c == 'o' && (red->type == token_apend
				|| red->type == token_red_output))
			f = red->fd;
		if (c == 'i' && (red->type == token_herd
				|| red->type == token_red_input))
			f = red->fd;
		red = red->next;
	}
	return (f);
}

int	init_infile_outfile(t_str *red, t_ast *node)
{
	int	flag;

	flag = 0;
	if (check_redout(red))
	{
		flag = outfile(red);
		if (flag == 0)
			node->cmd.outfile = get_last_fd(red, 'o');
	}
	if (check_redin(red))
	{
		flag = infile(red);
		if (flag == 0)
			node->cmd.infile = get_last_fd(red, 'i');
	}
	return (flag);
}

void	ft_quit_signal(int sig)
{
	(void)sig;
	write(1, "Quit", 5);
}
