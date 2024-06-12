/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:26:03 by maamichaima       #+#    #+#             */
/*   Updated: 2024/06/12 19:18:55 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
t_env	*v;
void	lst_token(char *ligne, t_token **head)
{
	char	*token;

	while (*ligne != '\0')
	{
		token = get_next_token(ligne);
		if (!token)
			break ;
		ft_lstadd_back(head, ft_lstnew(token));
	}
}

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

void	wait_(t_ast *root)
{
	if (root->type == token_cmd)
		waitpid(root->cmd.pid, NULL, 0);
	else
	{
		wait_(root->left);
		wait_(root->right);
	}
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

int	main(int c, char **av, char **env)
{
	char	*input;
	t_token	*head;
	t_ast	*root;
	
	
	v = get_env_lst(env);
	while (1)
	{
		input = readline("bash$ ");
		if (!input)
			break ;
		if (*input)
			add_history(input);
		head = NULL;
		lst_token(input, &head);
		if (is_valid_token(head) == 0)
			printf("pas valide\n");
		else if (head)
		{
			root = parse_and_or(head);
			init_ast(root, v);
			execut_all_here_doc(root);
			executer_tree(root, root, &v);
			close_(root);
			wait_(root);
		}
		free(input);
	}
	return (0);
}
