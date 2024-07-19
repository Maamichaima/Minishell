/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_close.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 21:26:53 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/19 01:43:13 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_(t_ast *root, t_env *env)
{
	int	status;

	status = 0;
	if (root->type == token_cmd)
	{
		waitpid(root->cmd.pid, &status, 0);
		if (WIFEXITED(status) && root->cmd.pid != 0)
			set_content_f(env, "?", ft_itoa(WEXITSTATUS(status)));
		else if (WIFSIGNALED(status) && root->cmd.pid != 0)
			set_content_f(env, "?", ft_itoa(128 + WTERMSIG(status)));
	}
	else
	{
		wait_(root->left, env);
		wait_(root->right, env);
	}
	return (status);
}

void	close_(t_ast *root)
{
	if (root->type == token_cmd)
	{
		if (root->cmd.infile != 0)
			close(root->cmd.infile);
		if (root->cmd.outfile != 1)
			close(root->cmd.outfile);
	}
	else
	{
		close_(root->left);
		close_(root->right);
	}
}
