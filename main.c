/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:26:03 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/15 21:36:13 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		sig_flag = 0;

void	print(t_ast *root)
{
	printf("        %d       \n", root->type);
	if (root->left && root->right)
		printf(" %s           %s \n", root->left->cmd.path,
			root->right->cmd.path);
}

void	printf_tree(t_ast *root)
{
	if (!root)
		return ;
	print(root);
	if (root->left && (root->left->type == token_pipe
			|| root->left->type == token_and || root->left->type == token_or))
		printf_tree(root->left);
	if (root->right && (root->right->type == token_pipe
			|| root->right->type == token_and || root->right->type == token_or))
		printf_tree(root->right);
}

void	start_minishell(t_token *head, t_env *v)
{
	t_ast	*root;
	t_token	*t;

	t = is_valid_token(head);
	if (t && check_herdoc(head, v))
		error_syntax(t);
	else if (t)
		error_syntax(t);
	else if (head)
	{
		root = parse_and_or(head);
		init_ast(root, v);
		execut_all_here_doc(root, v);
		executer_tree(root, root, &v);
		close_(root);
		wait_(root, v);
	}
}

void	control_c(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	if (!sig_flag)
	{
	// 	rl_replace_line("", 0);
	// 	rl_on_new_line();
	// 	rl_redisplay();
	}
}

int	main(int c, char **av, char **env)
{
	char	*input;
	t_token	*head;
	t_env	*v;

	(void)c;
	(void)av;
	v = get_env_lst(env);
	signal_handler();
	while (1)
	{
		input = readline("42_bash_$ ");
		sig_flag = 1;
		if (!input)
			ctl_d(v);
		if (*input)
			add_history(input);
		head = NULL;
		lst_token(input, &head);
		start_minishell(head, v);
		ft_malloc(0, 'f');
		sig_flag = 0;
		signal(SIGQUIT, SIG_IGN);
		free(input);
	}
	exit(0);
}
