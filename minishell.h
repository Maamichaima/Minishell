/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 13:55:55 by maamichaima       #+#    #+#             */
/*   Updated: 2024/05/22 12:23:11 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#define READLINE_LIBRARY
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

typedef	enum
{
	token_pipe,
	token_red_input,
	token_red_output,
	token_herd,
	token_expand,
	token_or,
	token_and,
	token_back_ope,
	token_word
}	token_type;

typedef struct s_token
{
	char *token;
	token_type type;
	struct s_token *next;
	struct s_token *prev;
}	t_token;

t_token	*ft_lstnew(char *content);
t_token	*ft_lstlast(t_token *lst);
void	ft_lstadd_back(t_token **lst, t_token *new);
int		ft_isalpha(int c);
int 	is_symbol(char c);
char	*get_next_token(char *s);
int check_pipe(t_token *head);
 int check_string(t_token *head);
#endif