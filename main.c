/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:26:03 by maamichaima       #+#    #+#             */
/*   Updated: 2024/05/22 12:23:25 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
	
void lst_token(char *ligne, t_token **head)
{
	char *token;
	
	while(*ligne != '\0')
	{
		token = get_next_token(ligne);
		if(!token)
			break;
		ft_lstadd_back(head, ft_lstnew(token));
	}
}

int main(int c, char **v) {
    char *input;
	t_token *head;

    while (input) 
	{
        input = readline("bash$ ");
        if (*input)
            add_history(input);
		head = NULL;
        lst_token(input, &head);
		printf("%d\n ",  check_string(head));
		// while(head != NULL)
		// {
		// 	printf("%s   %d \n", head->token, head->type);
		// 	head = head->next;
		// }
        free(input);
    }
    return 0;
}
