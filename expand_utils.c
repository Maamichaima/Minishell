/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:25:50 by maamichaima       #+#    #+#             */
/*   Updated: 2024/07/17 16:18:14 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_quotes_dollar(char *str)
{
	int		i;
	int		j;
	char	*with_quotes;

	if (!str || !str[0])
		return (str);
	j = 0;
	i = 0;
	with_quotes = ft_malloc(sizeof(char) * (ft_strlen(str) + 4), 'a');
	if (!with_quotes)
		return (NULL);
	with_quotes[0] = '"';
	with_quotes[1] = '$';
	i += 2;
	while (str[j])
	{
		with_quotes[i] = str[j];
		i++;
		j++;
	}
	with_quotes[i] = '"';
	with_quotes[i + 1] = '\0';
	return (with_quotes);
}

void	inisialiser_ite(t_ite *ite)
{
	ite->i = 0;
	ite->j = 0;
}

char	*hmad(char *s)
{
	t_ite	t;
	char	*tmp;
	char	*key;

	inisialiser_ite(&t);
	tmp = ft_malloc(sizeof(char) * 256, 'a');
	if (ft_strchr(s, '$'))
	{
		while (s[t.i])
		{
			if (s[t.i] == '$' && !check_quotes(s, t.i, 0) && check_equal(s,
					t.i))
			{
				t.i++;
				key = get_expand_value(s + t.i);
				copy(tmp, add_quotes_dollar(key));
				t.j += ft_strlen(key) + 2;
				t.i += ft_strlen(key);
			}
			else
				tmp[t.j++] = s[t.i++];
		}
		return (tmp);
	}
	return (s);
}

int len_value(char *str)
{
	int i;
	int len;

	i = 0;
	len = 0;
	if(!str)
		return 0;
	while(str[i] && (ft_isalpha(str[i]) || ft_isnum(str[i]) || str[i] == '_'))
	{
		i++;
		len++;
	}
	return len;
}

char	*get_expand_value(char *str)
{
	int		j;
	char	*val;

	if(!str)
		return(NULL);
	if (str[0] == '?')
		return (ft_strdup_in_gar("?"));
	val = ft_malloc(sizeof(char) * (len_value(str) + 1), 'a');
	j = 0;
	while (*str && (ft_isalpha(*str) || ft_isnum(*str) || *str == '_'))
	{
		val[j++] = *str;
		str++;
	}
	val[j] = '\0';
	return (val);
}

int	check_ex(char *s, char c, int i)
{
	if (s[i] == '$' && check_quotes(s, i, c) != -1 && (ft_isalpha(s[i + 1])
			|| ft_isnum(s[i + 1]) || s[i + 1] == '_' || s[i + 1] == '?'))
		return (1);
	return (0);
}
