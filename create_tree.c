/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:38:54 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/12 02:09:07 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
