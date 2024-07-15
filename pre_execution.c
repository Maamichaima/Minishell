/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pre_execution.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:17:45 by rraida-           #+#    #+#             */
/*   Updated: 2024/07/15 18:40:04 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inisialiser_pipe(t_ast *root)
{
	int	pip[2];

	pipe(pip);
	root->left->cmd.outfile = pip[1];
	if (root->right->type == token_cmd)
		root->right->cmd.infile = pip[0];
	else
		root->right->left->cmd.infile = pip[0];
}

void	init_ast(t_ast *root, t_env *env)
{
	if (root->type == token_pipe)
	{
		inisialiser_pipe(root);
		init_ast(root->right, env);
	}
}

int	check_redout(t_str *red)
{
	while (red)
	{
		if (red->type == token_apend || red->type == token_red_output)
			return (1);
		red = red->next;
	}
	return (0);
}

int	check_redin(t_str *red)
{
	while (red)
	{
		if (red->type == token_red_input || red->type == token_herd)
			return (1);
		red = red->next;
	}
	return (0);
}

int	check_redherdoc(t_str *red)
{
	while (red)
	{
		if (red->type == token_herd)
			return (1);
		red = red->next;
	}
	return (0);
}
