/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 15:17:45 by rraida-           #+#    #+#             */
/*   Updated: 2024/05/27 20:48:26 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    inisialiser_pipe(t_ast *root)
{
    int pip[2];

    pipe(pip);
    root->left->cmd.outfile = pip[0];
    if(root->right->type == token_cmd)
        root->right->cmd.infile = pip[1];
    else
        root->right->left->cmd.infile = pip[1];
}

void    search_ast(t_ast *root,t_env *env)
{
    if(root->type == token_pipe)
    {
        inisialiser_pipe(root);
        initialize_cmd(root->left,env);
        search_ast(root->right,env);
    }
    else
        initialize_cmd(root,env);
}

void   initialize_cmd(t_ast *node,t_env *env)
{
    t_cmd  tt;
    
   //printf("%p\n",node.cmd->args);
    node->cmd.args = list_to_table(node->args);
    printf("%s \n", node->cmd.args[1]);
    node->cmd.path = correct_path(get_paths(env),node->cmd.args[0]);
    printf("%s\n",node->cmd.path);
    // if(node->red)
    // {
    //     // while(node->red)
    //     // {
    //     //     if(node->red->type == token_herd)
    //     //         // infile = pipe_herd[0];
    //     //     if(node->red->type == token_red_input)
    //     //         // infile = functons;
    //     //     if(node->)
            
    //     // }
    // }

}