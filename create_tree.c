/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:38:54 by maamichaima       #+#    #+#             */
/*   Updated: 2024/05/25 15:57:30 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_ast	*lstnew_ast(token_type type, t_str *cmd, t_str *red)
{
	t_ast	*l;

	l = malloc(sizeof(t_ast));
	if (!l)
		return (NULL);
	l->type = type;
	l->args = cmd;
	l->cmd = NULL;
	l->red = red;
	l->right = NULL;
	l->left = NULL;
	return (l);
}

t_str	*lst_new_str(char *content, token_type type)
{
	t_str	*l;

	l = malloc(sizeof(t_str));
	if (!l)
		return (NULL);
	l->str = content;
	l->type = type;
	l->next = NULL;
	return (l);
}

t_str	*ft_lstlast_str(t_str *lst)
{
	if (lst == NULL)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back_str(t_str **lst, t_str *new)
{
	t_str	*t;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		t = ft_lstlast_str(*lst);
		t->next = new;
	}
}

t_str	*jbdi_red(t_token *lst)
{
	t_str	*red;

	red = NULL;
	while (lst)
	{
		if (is_redirectien(lst->type))
			ft_lstadd_back_str(&red, lst_new_str(lst->next->token, lst->type));
		lst = lst->next;
	}
	return (red);
}

t_str	*jbdi_cmd(t_token *lst)
{
	t_str	*cmd;

	cmd = NULL;
	while (lst)
	{
		if ((!lst->prev || !is_redirectien(lst->prev->type))
			&& !is_redirectien(lst->type))
			ft_lstadd_back_str(&cmd, lst_new_str(lst->token, lst->type));
		lst = lst->next;
	}
	return (cmd);
}

t_ast	*parse_cmd(t_token *lst)
{
	t_ast	*cmd;

	cmd = lstnew_ast(token_cmd, jbdi_cmd(lst), jbdi_red(lst));
	return (cmd);
}

t_ast	*parse_pipe(t_token *lst)
{
	t_ast	*root;
	t_token	*h_left;
	t_token	*h_right;

	h_left = lst;
	while (lst)
	{
		if (lst->type == token_pipe)
		{
			h_right = lst->next;
			lst->prev->next = NULL;
			root = lstnew_ast(lst->type, NULL, NULL);
			root->left = parse_cmd(h_left);
			root->right = parse_pipe(h_right);
			return (root);
		}
		lst = lst->next;
	}
	return (parse_cmd(h_left));
}

t_ast	*parse_and_or(t_token *lst)
{
	t_ast	*root;
	t_token	*h_left;
	t_token	*h_right;

	h_left = lst;
	while (lst)
	{
		if (lst->type == token_or || lst->type == token_and)
		{
			h_right = lst->next;
			lst->prev->next = NULL;
			root = lstnew_ast(lst->type, NULL, NULL);
			root->left = parse_pipe(h_left);
			root->right = parse_and_or(h_right);
			return (root);
		}
		lst = lst->next;
	}
	return (parse_pipe(h_left));
}
