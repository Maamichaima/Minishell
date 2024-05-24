/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:26:03 by maamichaima       #+#    #+#             */
/*   Updated: 2024/05/23 23:34:18 by maamichaima      ###   ########.fr       */
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

void printf_tree(t_ast *root)
{

    if (!root)
        return ;
    printf("     %d   ", root->type);
    if (root->right)
        printf_tree(root->right);
    if (root->left)
        printf_tree(root->left);
    printf("\n");
}

int	main(int c, char **v)
{
	char	*input;
	t_token	*head;
	t_ast	*root;
	t_str *red;


	while (1)
	{
		input = readline("bash$ ");
		if (*input)
			add_history(input);
		head = NULL;
		lst_token(input, &head);
		if (is_valid_token(head) == 0)
			printf("pas valide\n");
		else
		{
			// root = parse_pipe(head);
			// red = jbdi_red(head);
			// printf_tree(root);
			while (red != NULL)
			{
				printf("%s   %d \n", red->str, red->type);
				red = red->next;
			}
		}
		free(input);
	}
	return (0);
}
