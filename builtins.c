/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:43:31 by rraida-           #+#    #+#             */
/*   Updated: 2024/05/31 00:32:54 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_builtin(t_str cmd)
{
    if(ft_strcmp(cmd.str,"cd") == 0 || ft_strcmp(cmd.str,"echo")  == 0|| 
    ft_strcmp(cmd.str,"pwd")== 0 || ft_strcmp(cmd.str,"export")== 0 ||
    ft_strcmp(cmd.str,"unset")== 0 || ft_strcmp(cmd.str,"env")== 0 || ft_strcmp(cmd.str,"exit")== 0)
        return(1);
    return(0);
}

// void ft_cd(t_ast *root,t_env *env)
// {
//     while(env)
//     {
//         if(ft_strcmp(env->key, "HOME") == 0)
//             env->value = root->args->str;
//         env = env->next;
//     }
// }

// void    ft_pwd(t_env *env)
// {
//         char *path;
//         while(env)
//         {
//             if(ft_strcmp(env->key, "PWD") == 0)
//             path = malloc(sizeof(char) * ft_strlen());
            
//         }
        
//         printf("%s\n",getcwd(path,NULL));
        
// }
