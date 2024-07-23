/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:02:14 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/19 23:47:46 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_herdoc(t_token *head, t_env *env)
{
	int	status;
	int	flag;

	flag = 0;
	while (head)
	{
		if (head->type == token_herd && head->next
			&& head->next->type == token_word)
		{
			flag = 1;
			open_here_doc(head->next->token, env);
			wait(&status);
			if (status)
				break ;
		}
		head = head->next;
	}
	if (head == NULL && flag == 1)
		return (1);
	return (flag);
}

t_token	*is_valid_token(t_token *lst)
{
	while (lst)
	{
		if (is_redirectien(lst->type))
		{
			if ((!lst->next) || lst->next->type != token_word)
				return (lst);
		}
		if (lst->type == token_pipe)
		{
			if (!lst->prev || !lst->next || is_valide_pipe(lst))
				return (lst);
		}
		if (lst->type == token_word)
		{
			if (!is_valid_word(lst->token))
				return (lst);
		}
		lst = lst->next;
	}
	return (NULL);
}

void	error_syntax(t_env *v)
{
	write(2, "bash: syntax error near unexpected token \n", 43);
	set_content(v, "?", ft_itoa(2));
}

void	ft_exit_free(t_env *env, int e)
{
	(void)env;
	clear_env(env);
	ft_malloc(0, 'f');
	exit(e);
}

void	message_error(char *str, t_env *env)
{
	if (ft_strchr(str, '/'))
	{
		if (access(str, F_OK) == -1)
		{
			perror(str);
			ft_exit_free(env, 127);
		}
		if (access(str, X_OK) == -1)
		{
			perror(str);
			ft_exit_free(env, 126);
		}
	}
	if (access(str, F_OK | X_OK) == 0)
	{
		write(2, "bash: ", 7);
		write(2, str, ft_strlen(str));
		write(2, ": Is a directory\n", 18);
	}
	else
	{
		write(2, str, ft_strlen(str));
		write(2, ": command not found\n", 21);
	}
	ft_exit_free(env, 127);
}
