/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:43:31 by rraida-           #+#    #+#             */
/*   Updated: 2024/06/05 16:21:22 by rraida-          ###   ########.fr       */
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

void ft_cd(t_ast *root,t_env *env)
{
    char *old;
    char *new;
    t_env *tmp;

    tmp = env;
    old  = getcwd(NULL,0);
    if(root->args == NULL && root->args->str == NULL)
    {
        while(tmp)
        {
            if(ft_strcmp(tmp->key, "HOME") == 0)
                chdir(tmp->value);
            tmp = tmp->next;
        }
    }
    else
        chdir(root->args->str);
    new = getcwd(NULL,0);
    while(env)
    {
        if(ft_strcmp(env->key, "PWD") == 0)
          {  
            env->value = new;
            printf("%s\n",env->value);//path
            }
        if(ft_strcmp(env->key, "OLDPWD") == 0)  
          {  env->value = old;
            printf("%s\n",env->value);//path
            }
        env = env->next;
    }
}

void    ft_pwd(t_env *env)
{
    printf("%s\n",getcwd(NULL,0));
}

int check_key_in_env(t_env *env, t_str *args)
{
    int i = 0;
    
    while(env)
    {
        if(ft_strcmp(get_key(args->str), env->key) == 0)
        {
            while(args->str[i])
            {
                if(args->str[i] == '=' || args->str[i] == '+')
                    break;
                i++;
            }
            if(args->str[i] == '+' && args->str[i + 1] && args->str[i + 1] == '=')
            {
                env->path  = ft_strjoin(env->path, args->str + i + 2);
                env->value = ft_strjoin(env->value, args->str + i + 2);
            }
            else if(args->str[i] == '=')
            {
                env->value = get_value(args->str);
                env->path  = args->str;
            }
            return 1;
        }
        (env) = (env)->next;
    }
    return 0;
}

//syntaxe error + sorting by ascii +norminette
void    ft_export(t_ast *root, t_env *env)
{
    t_env *new = NULL;
    t_env *tmp = env;

    if(root->args && root->args->str && root->args->next == NULL)
    {
        while(env)
        {
            printf("declare -x %s=\"%s\"\n",env->key,env->value);
            (env) = (env)->next;
        }
    }
    else
    {
        root->args = root->args->next;
        while(root->args)
        {
            if(!check_key_in_env(env, root->args))
            {
                new = ft_lstnew_env(get_key(root->args->str), get_value(root->args->str),root->args->str);
                ft_lstadd_back_env(&tmp,new);
            }
            root->args = root->args->next;
        }
        while(tmp)
        {
            // printf("%s\n",tmp->path);
            tmp = tmp->next;
        }
    }
}

void    ft_unset(t_ast *root, t_env **env)
{
    t_env *new;
    new = *env;
    while(*env)
    {
        if(ft_strcmp(get_key(root->args->str),(*env)->key) == 0)
        {
            (*env)->prev->next =  (*env)->next;
            (*env)->next->prev =  (*env)->prev; 
        }
        (*env)= (*env)->next;
    }
   
}

// #include<stdio.h> 
 
// chdir function is declared 
// inside this header 
// #include<unistd.h> 
// int main() 
// { 
//     char *s; 
 
//     // printing current working directory 
//     printf("%s\n", getcwd(NULL,0)); 
 
//     // using the command 
//     chdir(".."); 
 
//     // printing current working directory 
//     printf("%s\n", getcwd(NULL, 0)); 
//     system("leaks a.out");
//     // after chdir is executed 
//     return 0; 
// }

