/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:05:16 by cmaami            #+#    #+#             */
/*   Updated: 2024/06/24 21:12:24 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	message_error(char *str)
{
	if (ft_strchr(str, '/'))
	{
		if (access(str, F_OK) == -1)
		{
			perror(str);
			exit(127);
		}
		if (access(str, X_OK) == -1)
		{
			perror(str);
			exit(126);
		}
	}
	write(2, str, ft_strlen(str));
	write(2, ": command not found\n", 21);
	exit(127);
} 

void	executer_cmd(t_cmd cmd, t_env *env, t_ast *const_root)
{
	dup2(cmd.infile, 0);
	dup2(cmd.outfile, 1);
	close_(const_root);
	execve(cmd.path, cmd.args, list_to_table_env(env));
	message_error(cmd.args[0]);
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

void	init_infile_outfile(t_str *red, t_ast *node)
{
	if (check_redout(red))
	{
		// close(node->cmd.outfile);
		outfile(red);
		node->cmd.outfile = get_last_fd(red, 'o');
	}
	if (check_redin(red))
	{
		// close(node->cmd.infile);
		infile(red);
		node->cmd.infile = get_last_fd(red, 'i');
	}
}

void	executer_tree(t_ast *root, t_ast *const_root, t_env **env)
{
	if (root->type == token_cmd)
	{
		if (root->args != NULL)
		{
			if (is_builtin(*(root->args)))
				check_bultins(root, const_root, env);
			else
			{
				root->cmd.pid = fork();
				if (root->cmd.pid == 0)
				{
					expand_node(root, *env);
					init_infile_outfile(root->red, root);
					root->cmd.args = list_to_table(root->args);
					root->cmd.path = correct_path(get_paths(*env), root->cmd.args[0]);
					executer_cmd(root->cmd, *env, const_root);
				}
			}
		}
	}
	else
	{
		executer_tree(root->left, const_root, env);
		executer_tree(root->right, const_root, env);
	}
}

void	fd_here_doc(t_str *red, t_env *env)
{
	while (red)
	{
		if (red->type == token_herd)
		{
			red->fd = open_here_doc(ignor(red->str), env);
			wait(NULL);
		}
		red = red->next;
	}
}

void	execut_all_here_doc(t_ast *root, t_env *env)
{
	t_str	*r;

	if (root->type == token_cmd)
		fd_here_doc(root->red, env);
	else
	{
		execut_all_here_doc(root->left, env);
		execut_all_here_doc(root->right, env);
	}
}
