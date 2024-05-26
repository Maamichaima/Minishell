/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:26:03 by maamichaima       #+#    #+#             */
/*   Updated: 2024/05/26 15:16:05 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		printf(" %d           %d \n", root->left->type, root->right->type);
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

int	main(int c, char **v, char **env)
{
	char	*input;
	t_token	*head;
	t_ast	*root;
	t_str	*red;
	t_str	*cmd;
	t_env	*tt;
	
	tt = get_env_lst(env);
	
	while(tt)
	{
		printf("%s\n",tt->value);
		tt = tt->next;
	}
	//puts(env[0]);
	// while (1)
	// {
	// 	input = readline("bash$ ");
	// 	if (!input)
	// 		break ;
	// 	if (*input)
	// 		add_history(input);
	// 	head = NULL;
	// 	lst_token(input, &head);
	// 	if (is_valid_token(head) == 0)
	// 		printf("pas valide\n");
	// 	else
	// 	{
	// 		root = parse_and_or(head);
	// 		// red = jbdi_red(head);
	// 		// cmd = jbdi_cmd(head);
	// 		printf_tree(root);
	// 		// while (cmd != NULL)
	// 		// {
	// 		// 	printf("%s   %d \n", cmd->str, cmd->type);
	// 		// 	cmd = cmd->next;
	// 		// }
	// 	}
	// 	free(input);
	// }
	//return (0);
}
