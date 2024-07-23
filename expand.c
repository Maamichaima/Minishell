/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:49:47 by rraida-           #+#    #+#             */
/*   Updated: 2024/07/22 14:33:23 by rraida-          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expandiliya(t_ite *ite, char *str, t_env *env, char *tmp)
{
	char	*key;
	char	*val;

	ite->i++;
	key = get_expand_value(str + ite->i);
	val = get_value_(key, env);
	if (val == NULL && ft_isnum(key[0]))
		val = key + 1;
	copy(tmp, val);
	ite->j += ft_strlen(val);
	ite->i += ft_strlen(key);
	return (tmp);
}

int	len_expand(char *str, char c, t_env *env)
{
	char	*key;

	int(len), (i);
	len = 0;
	i = 0;
	if (ft_strchr(str, '$'))
	{
		while (str[i])
		{
			if (str[i] == '$' && str[i + 1] == '"' && !check_quotes(str, i, 0))
				i++;
			else if (check_ex(str, c, i))
			{
				i++;
				key = get_expand_value(str + i);
				len += ft_strlen(get_value_(key, env));
				i += ft_strlen(key);
			}
			else
			{
				(i++);
				(len++);
			}
		}
	}
	return (len);
}

char	*expand(char *str, t_env *env, char c)
{
	char	*tmp;
	t_ite	ite;

	ite.i = 0;
	ite.j = 0;
	tmp = ft_malloc(sizeof(char) * (len_expand(str, c, env) + 1), 'a');
	tmp[0] = '\0';
	if (ft_strchr(str, '$'))
	{
		while (str[ite.i])
		{
			if (c != 'h' && (str[ite.i] == '$' && (str[ite.i + 1] == '"'
						|| str[ite.i + 1] == '\'') && !check_quotes(str, ite.i,
						0)))
				ite.i++;
			if (check_ex(str, c, ite.i))
				expandiliya(&ite, str, env, tmp);
			else
				tmp[ite.j++] = str[ite.i++];
		}
		return (tmp);
	}
	else
		return (str);
}

void	expand_red(t_str *red, t_env *env)
{
	while (red)
	{
		if (red->type != token_herd)
			red->str = expand(red->str, env, 'a');
		red = red->next;
	}
}

void	expand_node(t_ast *root, t_env *env)
{
	t_str	*arg;
	t_str	*new;
	int		i;
	char	**tmp;

	i = 0;
	new = NULL;
	tmp = NULL;
	arg = root->args;
	while (arg)
	{
		arg->str = hmad(arg->str);
		tmp = ft_split(expand(arg->str, env, 'a'), "\t\n ");
		while (tmp && tmp[i])
		{
			ft_lstadd_back_str(&new, lst_new_str(tmp[i], token_cmd));
			i++;
		}
		i = 0;
		arg = arg->next;
	}
	root->args = new;
	expand_red(root->red, env);
}
