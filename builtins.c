/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.3>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 23:43:31 by rraida-           #+#    #+#             */
/*   Updated: 2024/07/06 23:30:11 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char *get_content(char *key) --> i9leb fl HOME
// void  set_content(char *key, char *content)

void	error_cd(int a, char *str)
{
	if (a == 0)
	{
		write(2, "bash: cd:", 10);
		write(2, " HOME not set\n", 14);
	}
	else
	{
		write(2, "bash: cd: ", 11);
		perror(str);
	}
}

void	set_content(t_env *env,char *key, char *content)
{
	while (env)
	{
		if (ft_strcmp(env->key, key) == 0)
			env->value = content;
		env = env->next;
	}
}

int	ft_cd(char **args, t_env *env)
{
	char	*old;
	char	*new;
	char	*val;

	old = getcwd(NULL, 0);
	if (args[1] == NULL)
		val = get_value_("HOME", env);
	else
		val = args[1];
	if (!val)
	{
		error_cd(0, val);
		return 1;
	}
	else if (chdir(val) == -1)
	{
		error_cd(1, val);
		return 1;
	}
	new = getcwd(NULL, 0);
	set_content(env, "PWD", new);
	set_content(env, "OLDPWD", old);
	return 0;
}

int	ft_pwd(t_env *env)
{
	printf("%s\n", getcwd(NULL, 0));
	return (0);
}

int	check_key_in_env(t_env *env, char *args)
{
	int	i;

	i = 0;
	while (env)
	{
		if (ft_strcmp(get_key(args), env->key) == 0)
		{
			while (args[i])
			{
				if (args[i] == '=' || args[i] == '+')
					break ;
				i++;
			}
			if (args[i] == '+' && args[i + 1] && args[i + 1] == '=')
			{
				env->path = ft_strjoin(env->path, args + i + 2);
				env->value = ft_strjoin(env->value, args + i + 2);
			}
			else if (args[i] == '=')
			{
				env->value = ignor(get_value(args));
				env->path = args;
			}
			return (1);
		}
		(env) = (env)->next;
	}
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

int	ft_export(char **args, t_env *env)
{
	t_env	*new;
	t_env	*tmp;
	char	**key;
	int i = 0;

	new = NULL;
	tmp = env;

	if (args[0] && !args[1])
	{
		// key = sort_table(table_of_key(env));
		ft_write_export(sort_table(table_of_key(env)), env);
	}
	else
	{
		i++;
		while (args[i])
		{
			if (valide_key(args[i]) == 0)
			{
				ft_error_export(args[i]);
				return 1;
			}
			else if (!check_key_in_env(env, args[i]))
			{
				new = ft_lstnew_env(get_key(args[i]),
						ignor(get_value(args[i])), args[i]);
				ft_lstadd_back_env(&tmp, new);
			}
			i++;
		}
	}
	return 0;
}

int	supp(char *key, t_env **env)
{
	t_env	*new;
	int found = 0;

	new = *env;
	while (new)
	{
		if (ft_strcmp(get_key(key), new->key) == 0)
		{
			if ((new)->prev == NULL)
			{
				(*env) = (*env)->next;
				(*env)->prev = NULL;
			}
			else if (!new->next)
			{
				new->prev->next = NULL;
				return 1;
			}
			else
			{
				new->prev->next = new->next;
				new->next->prev = new->prev;
			}
			found = 1;
		}
		new = new->next;
	}
	return found;
}

int	ft_unset(char **args, t_env **env)
{
	t_env	*new;
	int i;
	int found = 0;

	new = *env;
	i = 0;
	if (!args[1])
		return 1;
	i++;
	while (args[i])
	{
		if (ft_strcmp(args[i], "_") != 0)
			found = supp(args[i], env);
		i++;
	}
	return (found);
}

int	ft_env(t_env *env) // env (dhfbuhbshb || path)
{
	while (env)
	{
		if (env->value == NULL)
			(env) = (env)->next;
		else if(ft_strcmp("_",env->key) == 0)
			printf("%s=/usr/bin/env\n", env->key);
		else
			printf("%s=%s\n", env->key, env->value);
		(env) = (env)->next;
	}
	return 0;
}

int	check_flag(char *flag)
{
	int	i;

	i = 0;
	if (flag[i] == '-' && flag[i])
	{
		i++;
		if (flag[i] == '\0')
			return (1);
		while (flag[i] && flag[i] == 'n')
		{
			i++;
		}
		if (flag[i] == '\0')
			return (0);
	}
	return (1);
}

int	ft_echo(char **args, t_env *env)
{
	int		new_line;
	int i;

	i = 0;
	if (args[1] == NULL)//root->args && !root->args->next)
	{
		printf("\n");
		return 0;
	}
	new_line = 0;
	i++;
	while (args[i] && check_flag(args[i]) == 0)
	{
		i++;
		new_line = 1;
	}
	while (args[i])
	{
		printf("%s", args[i]);
		if (args[i])
			printf(" ");
		i++;
	}
	if (new_line != 1)
		printf("\n");
	return 0;
}

int    ft_exit(char **args)
{
    if(args[0] && !args[1])
    {
        write(2,"exit\n",6);
        exit(0);
    }
    else if(str_is_num(args[1]) || (!str_is_num(args[1]) && ft_strlen(args[1]) > 12))
    {
        write(2, "exit\nbash: exit: ", 18);
        write(2, args[1], ft_strlen(args[1]));
        write(2, ": numeric argument required\n", 29);
        exit(255);
    }
    else if (args[0] && !str_is_num(args[1]) && args[2] == NULL)
    {
        write(2, "exit\n", 6);
        exit(ft_atoi(args[1]));
    }
    else
    {
        write(2, "exit\n", 6);
        write(2, "bash: exit: too many arguments\n", 32);
		return (1);
    }
	return (0);
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
