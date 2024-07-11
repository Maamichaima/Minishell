/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:50:22 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/06 00:28:27 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0'))
		i++;
	return (s1[i] - s2[i]);
}

token_type	set_type(char *content)
{
	token_type	type;

	if (!ft_strcmp(content, "<"))
		type = token_red_input;
	else if (!ft_strcmp(content, ">"))
		type = token_red_output;
	else if (!ft_strcmp(content, "<<"))
		type = token_herd;
	else if (!ft_strcmp(content, ">>"))
		type = token_apend;
	else if (!ft_strcmp(content, "|"))
		type = token_pipe;
	else if (!ft_strcmp(content, "||"))
		type = token_or;
	else if (!ft_strcmp(content, ")"))
		type = token_right_par;
	else if (!ft_strcmp(content, "("))
		type = token_left_par;
	else if (!ft_strcmp(content, "&"))
		type = token_back_ope;
	else if (!ft_strcmp(content, "&&"))
		type = token_and;
	else
		type = token_word;
	return (type);
}

t_token	*ft_lstnew(char *content)
{
	t_token	*l;

	if (!content)
		return (NULL);
	l = ft_malloc(sizeof(t_token), 'a');
	if (!l)
		return (NULL);
	l->token = content;
	l->type = set_type(content);
	l->next = NULL;
	l->prev = NULL;
	return (l);
}

t_token	*ft_lstlast(t_token *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_token **lst, t_token *new)
{
	t_token	*t;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		t = ft_lstlast(*lst);
		t->next = new;
		new->prev = t;
	}
}
