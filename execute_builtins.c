/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:50:38 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/12 11:39:54 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execut_bultin(t_ast *root, t_env **env)
{
	t_cmd	cmd;

	root->cmd.args = list_to_table(root->args);
	ignor_args(root->cmd.args);
	cmd = root->cmd;
	if (ft_strcmp(cmd.args[0], "export") == 0)
		return (ft_export(root->cmd.args, *env));
	else if (ft_strcmp(cmd.args[0], "cd") == 0)
		return (ft_cd(root->cmd.args, *env));
	else if (ft_strcmp(cmd.args[0], "pwd") == 0)
		return (ft_pwd(*env));
	else if (ft_strcmp(cmd.args[0], "unset") == 0)
		return (ft_unset(root->cmd.args, env));
	else if (ft_strcmp(cmd.args[0], "echo") == 0)
		return (ft_echo(root->cmd.args, root->cmd.outfile));
	else if (ft_strcmp(cmd.args[0], "exit") == 0)
		return (ft_exit(root->cmd.args));
	else if (ft_strcmp(cmd.args[0], "env") == 0)
		return (ft_env(*env));
	return (0);
}

int	execute_in_parent(t_ast *root, t_env **env)
{
	int	stdin;
	int	stdout;
	int	status;

	stdin = dup(0);
	stdout = dup(1);
	init_infile_outfile(root->red, root);
	dup2(root->cmd.infile, 0);
	dup2(root->cmd.outfile, 1);
	status = execut_bultin(root, env);
	dup2(stdin, 0);
	dup2(stdout, 1);
	return (status);
}

int	check_bultins(t_ast *root, t_ast *const_root, t_env **env)
{
	int	status;

	status = 0;
	if (count_cmd(const_root) > 1)
	{
		root->cmd.pid = fork();
		if (root->cmd.pid == 0)
		{
			init_infile_outfile(root->red, root);
			dup2(root->cmd.infile, 0);
			dup2(root->cmd.outfile, 1);
			close_(const_root);
			status = execut_bultin(root, env);
			exit(status);
		}
	}
	else
		status = execute_in_parent(root, env);
	return (status);
}
