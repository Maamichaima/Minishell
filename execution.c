/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:05:16 by cmaami            #+#    #+#             */
/*   Updated: 2024/07/23 16:24:51 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executer_cmd(t_cmd cmd, t_env *env, t_ast *const_root)
{
	char	**t;

	dup2(cmd.infile, 0);
	dup2(cmd.outfile, 1);
	close_(const_root);
	t = list_to_table_env(env);
	execve(cmd.path, cmd.args, t);
	message_error(cmd.args[0], env);
}

void	prepare_cmd(t_ast *root, t_env *env)
{
	root->cmd.args = list_to_table(root->args);
	ignor_args(root->cmd.args);
	if (init_infile_outfile(root->red, root) == 1)
		ft_exit_free(env, 1);
	if (root->cmd.args)
	{
		root->cmd.path = correct_path(get_paths(env), root->cmd.args[0]);
		if (!root->cmd.path)
			root->cmd.path = ft_strdup_in_gar("");
	}
	else
		root->cmd.path = NULL;
}

void	set_last_env_value(t_ast *root, t_env *env)
{
	char	*tmp;

	if (!root->args)
		return ;
	while (env)
	{
		if (ft_strcmp("_", env->key) == 0)
		{
			while (root->args->next)
				root->args = root->args->next;
			tmp = env->value;
			env->value = ft_strdup(root->args->str);
			if (tmp)
				free(tmp);
		}
		env = env->next;
	}
}

void	execute_node(t_ast *root, t_ast *const_root, t_env **env, int count)
{
	int	e;

	if ((root->args) && is_builtin(*(root->args)))
	{
		e = check_bultins(root, const_root, env, count);
		set_content(*env, "?", ft_itoa(e));
	}
	else
	{
		root->cmd.pid = fork();
		if (root->cmd.pid == 0)
		{
			prepare_cmd(root, *env);
			if (root->args)
				executer_cmd(root->cmd, *env, const_root);
			ft_exit_free(*env, 0);
		}
	}
}

void	executer_tree(t_ast *root, t_ast *const_root, t_env **env)
{
	signal(SIGQUIT, ft_quit_signal);
	if (root->type == token_cmd)
	{
		expand_node(root, *env);
		execute_node(root, const_root, env, count_cmd(const_root));
		set_last_env_value(root, *env);
	}
	else
	{
		executer_tree(root->left, const_root, env);
		executer_tree(root->right, const_root, env);
	}
}
