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

void    inisialiser_pipe(t_ast *root)
{
    int pip[2];

    pipe(pip);
    root->left->cmd->outfile = pip[0];
    if(root->right->type == token_cmd)
        root->right->cmd->infile = pip[1];
    else
        root->right->left->cmd->infile = pip[1];
}

void    search_ast(t_ast *root)
{
    if(root->type = token_pipe)
    {
        inisialiser_pipe(root);
        search_ast(root->right);
    }
    else
        initialize_cmd(root);
}

void set_data()
{
    
}

void   initialize_cmd(t_ast *node)
{
    t_cmd  cmd;

    if(check_redout())
    {
        close(cmd.outfile);
        cmd.outfile = outfile(node->red);
        // while(node->red)
        // {
        //     if(node->red->type == token_herd)
        //         // infile = pipe_herd[0];
        //     if(node->red->type == token_red_input)
        //         // infile = functons;
        //     // if(node->)
            
        // }
    }
}