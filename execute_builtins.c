/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bultins.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 19:50:38 by maamichaima       #+#    #+#             */
/*   Updated: 2024/06/07 22:37:05 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execut_bultin(t_ast *root, t_env **env)
{
	t_cmd	cmd;

	cmd = root->cmd;
	if (ft_strcmp(cmd.args[0], "export") == 0)
		ft_export(root, *env);
	else if (ft_strcmp(cmd.args[0], "cd") == 0)
		ft_cd(root, *env);
	else if (ft_strcmp(cmd.args[0], "pwd") == 0)
		ft_pwd(*env);
	else if (ft_strcmp(cmd.args[0], "unset") == 0)
		ft_unset(root, env);
	else if (ft_strcmp(cmd.args[0], "echo") == 0)
		ft_echo(root, *env);
	else if (ft_strcmp(cmd.args[0], "exit") == 0)
		ft_exit(root);
	else if (ft_strcmp(cmd.args[0], "env") == 0)
		ft_env(*env);
}
