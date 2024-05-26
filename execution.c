/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:17:45 by rraida-           #+#    #+#             */
/*   Updated: 2024/05/26 16:55:43 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    search_ast(t_ast *root)
{
    while(root)
    {
        if(root->type = token_pipe)
        {
            execute_cmd(root->left);
            search_ast(root->right);
        }
        execute_cmd(root);
    }
}
void set_data()
{
    
}

void    execute_cmd(t_ast *node)
{
    pid_t pid;
    t_cmd  cmd;
    int pfd[2];
    pipe(pfd);
    if(node->cmd  && !node->red)
    {
        pid = fork();
        if(pid = 0)
        {
            set_data(cmd);
        }
    }
    else if( node->cmd && node->red)
    {
        
    }
    else
    
}