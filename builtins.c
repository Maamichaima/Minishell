/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:43:31 by rraida-           #+#    #+#             */
/*   Updated: 2024/06/07 22:50:50 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *get_content(char *key) --> i9leb fl HOME
// void  set_content(char *key, char *content)

void	ft_cd(t_ast *root, t_env *env)
{
	char	*old;
	char	*new;
	t_env	*tmp;

	tmp = env;
	old = getcwd(NULL, 0);
	if (root->args->next == NULL)
	{
		while (tmp)
		{
			if (ft_strcmp(tmp->key, "HOME") == 0)
				chdir(tmp->value);
			tmp = tmp->next;
		}
	}
	else
		chdir(root->args->next->str);
	new = getcwd(NULL, 0);
	while (env)
	{
		if (ft_strcmp(env->key, "PWD") == 0)
		{
			env->value = new;
			// printf("%s\n",env->value);//path
		}
		if (ft_strcmp(env->key, "OLDPWD") == 0)
		{
			env->value = old;
			// printf("%s\n",env->value);//path
		}
		env = env->next;
	}
}
void	ft_pwd(t_env *env)
{
	printf("%s\n", getcwd(NULL, 0));
}

int	check_key_in_env(t_env *env, t_str *args)
{
	int	i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(get_key(args->str), env->key) == 0)
		{
			while (args->str[i])
			{
				if (args->str[i] == '=' || args->str[i] == '+')
					break ;
				i++;
			}
			if (args->str[i] == '+' && args->str[i + 1] && args->str[i
				+ 1] == '=')
			{
				env->path = ft_strjoin(env->path, args->str + i + 2);
				env->value = ft_strjoin(env->value, args->str + i + 2);
			}
			else if (args->str[i] == '=')
			{
				env->value = get_value(args->str);
				env->path = args->str;
			}
			return (1);
		}
		(env) = (env)->next;
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

int	valide_key(char *str)
{
	if (str[0] == '_' || ft_isalpha(str[0]))
		return (1);
	return (0);
}

void	ft_error_export(char *str)
{
	write(2, "bash: export: ", 15);
	write(2, str, ft_strlen(str));
	write(2, ": not a valid identifier\n", 26);
}
// syntaxe error + sorting by ascii +norminette
void	ft_export(t_ast *root, t_env *env)
{
	t_env	*new;
	t_env	*tmp;
	char **key;

	new = NULL;
	tmp = env;
	if (root->args && root->args->str && root->args->next == NULL)
	{
		key = sort_table(table_of_key(env));
		ft_write_export(key, env);
	}
	else
	{
		root->args = root->args->next;
		while (root->args)
		{
			if (valide_key(root->args->str) == 0)
				ft_error_export(root->args->str);
			else if (!check_key_in_env(env, root->args))
			{
				new = ft_lstnew_env(get_key(root->args->str),
						get_value(root->args->str), root->args->str);
				ft_lstadd_back_env(&tmp, new);
			}
			root->args = root->args->next;
		}
	}
}

void	ft_unset(t_ast *root, t_env **env)
{
	t_env	*new;

	new = *env;
	while (new)
	{
		if (!root->args->next)
			return ;
		if (ft_strcmp(get_key(root->args->next->str), (new)->key) == 0)
		{
			
			if ((new)->prev == NULL)
			{
				(*env) = (*env)->next;
				(*env)->prev = NULL;
			}
			else if(!new->next)
				new = NULL;//_hadi makhasehach tmseh
			else
			{
				(new)->prev->next = (new)->next;
				(new)->next->prev = (new)->prev;
			}
		}
		(new) = (new)->next;
	}
}

void	ft_env(t_env *env)
{
	while (env)
	{
		if (env->value == NULL)
			(env) = (env)->next;
		else
		{
			printf("%s=%s\n", env->key, env->value);
			(env) = (env)->next;
		}
	}
	return ;
}

int	check_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag[i] == '-' && flag[i])
	{
		i++;
		if(flag[i] == '\0')
			return (1);
		while (flag[i] && flag[i] == 'n')
		{
			i++;
		}
		if(flag[i] == '\0')
			return (0);
	}
	return (1);
}

void	ft_echo(t_ast *root, t_env *env)
{
	int		new_line;
	t_str	*cmd;

	if (root->args && !root->args->next)
	{
		printf("\n");
		return ;
	}
	new_line = 0;
	cmd = root->args->next;

	while (cmd && check_flag(cmd->str) == 0)
	{
		cmd = cmd->next;
		new_line = 1;
	}
	while (cmd)
	{
		printf("%s", cmd->str);
		if (cmd->next)
			printf(" ");
		cmd = cmd->next;
	}
	if (new_line != 1)
		printf("\n");
}

void	ft_exit(t_ast *root)
{
	if (root->args && root->args->next && root->args->next->next == NULL)
	{
		if (!str_is_num(root->args->next->str))
			exit(ft_atoi(root->args->next->str));
		else
		{
			write(2, "exit\nbash: exit: ", 18);
			write(2, root->args->next->str, ft_strlen(root->args->next->str));
			write(2, ": numeric argument required\n", 29);
			exit(2);
		}
	}
	else if (root->args && root->args->next && root->args->next->next != NULL)
	{
		write(2, "exit\n", 6);
		write(2, "bash: exit: too many arguments\n", 32);
	}
	else if (root->args && !root->args->next)
		exit(0);
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
//     return (0);
// }
