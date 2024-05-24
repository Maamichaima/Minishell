/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tree.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:38:54 by maamichaima       #+#    #+#             */
/*   Updated: 2024/05/23 15:39:48 by maamichaima      ###   ########.fr       */
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
    l->cmd = cmd;
    l->red = red;
    l->right = NULL;
    l->left = NULL;
	return (l);
}



t_ast   *parse_cmd(t_token *lst)
{
    
    return (NULL);
}

t_ast *parse_pipe(t_token *lst)
{
    t_ast *root;
    t_token *h_left;
    t_token *h_right;

    h_left = lst;
    while(lst)
    {
        if(lst->type == token_pipe)
        {
            h_right =lst->next;
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
