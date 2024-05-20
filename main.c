/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 12:26:03 by maamichaima       #+#    #+#             */
/*   Updated: 2024/05/20 23:50:55 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "minishell.h"
#define READLINE_LIBRARY
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
// #include "/opt/homebrew/Cellar/readline/8.2.10/include/readline/readline.h"
// #include "/opt/homebrew/Cellar/readline/8.2.10/include/readline/history.h"

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}
int	is_symbole(int c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

// char **lexer(char *ligne)
// {
// 	int i;
// 	int len_char;
// 	char **lex;
// 	char **cmd;
// 	t_token token;
// 	len_char = 0;
// 	i = 0;
// 	while (ligne[i])
// 	{
// 		if(ft_isalpha(ligne[i]))
// 		{
// 			while(ligne[i] && ft_isalpha(ligne[i]))
// 			{
// 				i++;
// 				len_char++;
// 			}
// 			cmd = malloc(sizeof(char) * (len_char + 1));
// 			if(!cmd)
// 				return NULL;
// 			strncpy(cmd, ligne, len_char);
// 		}
// 		else if(ft_pipe(ligne[i]))
// 		{ 
// 			char *p = malloc(sizeof(char) * 2);
// 			// strncpy(p,)
// 		}
			
// 		i++;
// 	}
// }
char *get_token(char **arg)
{
	char *ligne = *arg;
	char *value = malloc(sizeof(char) * 256);
	int i = 0;
	while(*ligne && *ligne == ' ')
	{
		ligne++;
	}
	if(*ligne == '\0')
	{
		*arg = ligne;
	}
	if( *ligne && ft_isalpha(ligne[i]))
	{
		while(*ligne && ft_isalpha(*ligne))
		{
			value[i] = *ligne;
			i++;
			ligne++;
		}
		value[i] = '\0';
		*arg = ligne;
		return(value);
	}
	else if(*ligne && is_symbole(*ligne))
	{
		value[0] = *ligne;
		value[1] = '\0';
		ligne++;
		*arg = ligne;
		return(value);
	}
	return (NULL);
}

t_token	*ft_lstnew(char *content)
{
	t_token	*l;

	l = malloc(sizeof(t_token));
	if (!l)
		return (NULL);
	l->data = content;
	if(ft_isalpha(l->data[0]))
		*l->type = token_word;
	else
		*l->type = token_symbole;
	l->right = NULL;
	l->left = NULL;
	return (l);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->right != NULL)
		lst = lst->right;
	return (lst);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*t;

	if (!lst)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		t = ft_lstlast(*lst);
		t->right = new;
	}
}
//  t_token *create_tree(token data)
//  {
// 	t_token tree;
// 	ft_lstnew(data[0])
// 	tree->left = lst_new(data[1]);
// 	tree->right = lst_new(data[2]);

// 	return(tree);
//  }
	
int count_token(char *ligne)
{
	int i;
	// t_token *token;
	// t_token *tree;
	t_data token[3];
	//{data , type}
	int count = 0;
	i = 0;
	
	while(*ligne)
	{
		token[i]->data = get_token(&ligne);
		//ft_lstadd_back(&token, ft_lstnew(token));
		count++;
	}
	create_tree(data);
	return count;
}

int main(int c, char **v) {
    char *input;
	
    while (input) 
	{
        input = readline("bash$ ");
        if (*input)
            add_history(input);
        count_token(input);
        free(input);
    }
    return 0;
}
//gcc -L /opt/homebrew/Cellar/readline/8.2.10/lib