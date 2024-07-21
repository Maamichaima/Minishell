/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valide_syntax_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 19:39:09 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/15 21:10:57 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirectien(t_token_type type)
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
	j = -1;
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

int	is_valid_and_or(t_token *lst)
{
	if ((lst->next->type != token_word && !is_redirectien(lst->next->type))
		|| (lst->prev->type != token_word && !is_redirectien(lst->prev->type)))
		return (1);
	return (0);
}

int	is_valide_pipe(t_token *lst)
{
	if ((lst->prev->type != token_word) || (lst->next->type != token_word
			&& !is_redirectien(lst->next->type)))
		return (1);
	return (0);
}
