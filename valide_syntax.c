/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:02:14 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/14 15:37:02 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirectien(token_type type)
{
	if (type == token_red_input || type == token_red_output
		|| type == token_herd || type == token_apend)
		return (1);
	return (0);
}

int	is_valid_word(char *s)
{
	char	lock;
	int		i;
	int		j;

	i = 0;
	lock = 0;
	while (s[i])
	{
		if (!lock && (s[i] == '\'' || s[i] == '"'))
		{
			lock = s[i];
			j = i;
		}
		if (j != i && lock == s[i])
			lock = 0;
		i++;
	}
	if (!lock)
		return (1);
	else
		return (0);
}

int 	check_herdoc(t_token *head,t_env *env)
{
	int status;
	int flag = 0;
	while(head)
	{
		if(head->type == token_herd && head->next)
		{
			flag = 1;
			open_here_doc(head->next->token ,env);
			wait(&status);
			if (status)
				break ;
		}
		head = head->next;
	}
	if(head ==  NULL && flag == 1)
		return(1);
	return(flag);
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
		if (lst->type == token_or || lst->type == token_and)
		{
			if (!lst->prev || !lst->next)
				return (lst);
			if ((lst->next->type != token_word
					&& !is_redirectien(lst->next->type))
				|| (lst->prev->type != token_word
					&& !is_redirectien(lst->prev->type)))
				return (lst);
		}
		if (lst->type == token_pipe)
		{
			if (!lst->prev || !lst->next)
				return (lst);
			if ((lst->prev->type != token_word)
				|| (lst->next->type != token_word
					&& !is_redirectien(lst->next->type)))
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

void	error_syntax(t_token *t)
{
	if (t)
	{
		if (!is_redirectien(t->type))
		{
			write(2, "bash: syntax error near unexpected token '", 42);
			write(2, t->token, ft_strlen(t->token));
			write(2, "'\n", 2);
		}
		else
			write(2, "bash: syntax error near unexpected token `newline'\n",
				52);
	}
}

void	message_error(char *str)
{
	if (ft_strchr(str, '/'))
	{
		if (access(str, F_OK) == -1)
		{
			perror(str);
			exit(127);
		}
		if (access(str, X_OK) == -1)
		{
			perror(str);
			exit(126);
		}
	}
	if (access(str, F_OK) == 0)
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
	exit(127);
}
