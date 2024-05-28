/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmaami <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 15:05:16 by cmaami            #+#    #+#             */
/*   Updated: 2024/05/28 15:05:20 by cmaami           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    executer_tree(t_ast *root, t_env *env, char **ev)
{
    pid_t pid;
    if(root->type == token_cmd)
    {
        pid = fork();
        if(pid == 0)
        {
            // printf("%s\n", root->cmd.args[0]);
            // printf("%s\n", root->cmd.path);
            execve(*root->cmd.args, &root->cmd.path, ev);
            printf("hh\n");
            exit (1);
        }
    }
    // else
    // {
    //     executer_tree(root->left, env);
    //     executer_tree(root->right, env);
    // }
}
