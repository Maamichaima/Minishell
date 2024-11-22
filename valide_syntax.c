/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_syntax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:02:14 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/04 23:19:06 by rraida-          ###   ########.fr       */
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

t_token *is_valid_token(t_token *lst)
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
			if((lst->next->type != token_word && !is_redirectien(lst->next->type))
				|| (lst->prev->type != token_word && !is_redirectien(lst->prev->type)))
				return (lst->next);
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
