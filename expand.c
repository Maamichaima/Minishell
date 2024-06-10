/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 17:39:41 by maamichaima       #+#    #+#             */
/*   Updated: 2024/06/10 22:55:49 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str, int c)
{
	int lock;
	int i;
	int first;
	int last;

	i = 0;
	lock = 0;
	while(str[i])
	{
		if(lock == 0 && (str[i] == '\'' || str[i] == '"'))
		{
			lock = str[i];
			first = i;
		}
		else if(lock == str[i])
		{
			last = i;
			if(c < last && c > first)
				break;
			lock = 0;
		}
		i++;
	}
	if(lock == '\"')
		return 1;
	else if(lock == '\'')
		return -1;
	else
		return 0;
}

// int main ()
// {
// 	char *input;

// 	while(1)
// 	{
// 		input = readline(">");
// 		if (*input)
// 			add_history(input);
// 		printf("%d \n", check_quotes(input, 5));
// 	}
// }