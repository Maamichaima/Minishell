/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:05:16 by cmaami            #+#    #+#             */
/*   Updated: 2024/06/09 21:09:56 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	d;
	size_t	s;

	i = 0;
	s = ft_strlen(src);
	if (dstsize == 0 || dstsize <= ft_strlen(dst))
		return (s + dstsize);
	d = ft_strlen(dst);
	j = d;
	while (src[i] != '\0' && i < dstsize - d - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (d + s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		ls1;
	int		ls2;
	char	*p;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	p = malloc(sizeof(char) * (ls1 + ls2 + 1));
	if (!p)
		return (NULL);
	p[0] = '\0';
	ft_strlcat(p, s1, ls1 + 1);
	ft_strlcat(p, s2, ls1 + ls2 + 1);
	return (p);
}

void	executer_cmd(t_cmd cmd, t_env *env, t_ast *const_root)
{
	dup2(cmd.infile, 0);
	dup2(cmd.outfile, 1);
	close_(const_root);
	execve(cmd.path, cmd.args, list_to_table_env(env));
	write(2, cmd.args[0], ft_strlen(cmd.args[0]));
	write(2, ": command not found\n", 21);
	exit(127);
}

int get_last_fd(t_str *red, char c)
{
	int f;

	while (red)
	{
		if (c == 'o' && (red->type == token_apend || red->type == token_red_output))
			f = red->fd;
		if (c == 'i' && (red->type == token_herd || red->type == token_red_input))
			f = red->fd;
		red = red->next;
	}
	return(f);
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
		if(root->args != NULL)
		{
			if (is_builtin(*(root->args)))
				check_bultins(root, const_root, env);
			else
			{
				root->cmd.pid = fork();
				if (root->cmd.pid == 0)
				{
					init_infile_outfile(root->red, root);
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

void	fd_here_doc(t_str *red)
{
	while (red)
	{
		if (red->type == token_herd)
		{
			red->fd = open_here_doc(red->str);
			wait(NULL);
		}
		red = red->next;
	}
}

void	execut_all_here_doc(t_ast *root)
{
	t_str	*r;

	if (root->type == token_cmd)
		fd_here_doc(root->red);
	else
	{
		execut_all_here_doc(root->left);
		execut_all_here_doc(root->right);
	}
}
