/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:49:47 by rraida-           #+#    #+#             */
/*   Updated: 2024/06/30 19:31:44 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_quotes(char *str, int c, char h)
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
	if(lock == '\"' || h == 'h')
		return 1;
	else if(lock == '\'')
		return -1;
	else
		return 0;
}

char *get_expand_value(char *str)
{
    int j;
    
    char *val = malloc(sizeof(char ) *256);
    j = 0;
    while(*str && (ft_isalpha(*str) || ft_isnum(*str) || *str =='_'))
    {     
        val[j++] = *str;
        str++;
    }
    val[j] = '\0';
    return(val);
}

char    *expand(char *str, t_env *env, char c)
{
    int i;
    int k;
    char *key;
    char *val;
    char *tmp = ft_malloc(sizeof(char ) * 256, 'a');
    
    i = 0;
    k = 0;
	tmp[0] = '\0';
    if(ft_strchr(str, '$'))
    {   
        while(str[i])
        {
            if(str[i] == '$' && check_quotes(str, i, c) != -1)
            {
                i++;
                key = get_expand_value(str + i);
                val = get_value_(key, env);
				if(val == NULL && ft_isnum(key[0]))
					val = key + 1;
                tmp = ft_strjoin(tmp, val);
                k += ft_strlen(val);
                i += ft_strlen(key);
            }
            else
                tmp[k++] = str[i++];
			tmp[k] = '\0';
        }
		if(tmp[0] == '\0'|| tmp[1] == '\"')
			return NULL;
    	return(tmp);
    }
    else
       return(str);
}

void expand_node(t_ast *root, t_env *env)
{
	t_str *red;
	t_str *arg;
	t_str *new = NULL;
	int i = 0;
	char **tmp = NULL;

	red = root->red;
	arg = root->args;
	
	while(arg)
	{
		// if(ft_strchr(arg->str,'='))
		// 	tmp[i] = expand(arg->str, env, 'a');
		// else
			tmp = ft_split(expand(arg->str, env, 'a'), " \n\t\f");
		while(tmp && tmp[i])
		{
			ft_lstadd_back_str(&new, lst_new_str(tmp[i], token_cmd));
			i++;
		}
		i = 0;
		arg = arg->next;
	}
	root->args = new;
	while(red)
	{
		if(red->type != token_herd)
			red->str = expand(red->str, env, 'a');
		red = red->next;
	}
}

// int main(int ac, char **av, char **env)
// {
    
//     expand("hello$PWD$HOME", );
    
// }