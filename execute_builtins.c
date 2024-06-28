/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:50:38 by maamichaima       #+#    #+#             */
/*   Updated: 2024/06/27 13:52:44 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execut_bultin(t_ast *root, t_env **env)
{
	t_cmd	cmd;

	root->cmd.args = list_to_table(root->args);
	expand_node(root, *env);
	cmd = root->cmd;
	//args ??
	if (ft_strcmp(cmd.args[0], "export") == 0)
		ft_export(root->cmd.args, *env);
	else if (ft_strcmp(cmd.args[0], "cd") == 0)
		ft_cd(root->cmd.args, *env);
	else if (ft_strcmp(cmd.args[0], "pwd") == 0)
		ft_pwd(*env);
	else if (ft_strcmp(cmd.args[0], "unset") == 0)
		ft_unset(root->cmd.args, env);
	else if (ft_strcmp(cmd.args[0], "echo") == 0)
		ft_echo(root->cmd.args, *env);
	else if (ft_strcmp(cmd.args[0], "exit") == 0)
		ft_exit(root->cmd.args);
	else if (ft_strcmp(cmd.args[0], "env") == 0)
		ft_env(*env);
}

void	execute_in_parent(t_ast *root, t_env **env)
{
	int	stdin;
	int	stdout;

	stdin = dup(0);
	stdout = dup(1);
	init_infile_outfile(root->red, root);
	dup2(root->cmd.infile, 0);
	dup2(root->cmd.outfile, 1);
	execut_bultin(root, env);
	dup2(stdin, 0);
	dup2(stdout, 1);
}

void	check_bultins(t_ast *root, t_ast *const_root, t_env **env)
{
	if (count_cmd(const_root) > 1)
	{
		root->cmd.pid = fork();
		if (root->cmd.pid == 0)
		{
			init_infile_outfile(root->red, root);
			dup2(root->cmd.infile, 0);
			dup2(root->cmd.outfile, 1);
			close_(const_root);
			execut_bultin(root, env);
			exit(0);
		}
	}
	else
		execute_in_parent(root, env);
}
