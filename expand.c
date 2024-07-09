/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:49:47 by rraida-           #+#    #+#             */
/*   Updated: 2024/07/09 15:45:19 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	check_quotes(char *str, int c, char h)
// {
// 	int lock;
// 	int i;
// 	int first;
// 	int last;

// 	i = 0;
// 	lock = 0;
// 	while(str[i])
// 	{
// 		if(lock == 0 && (str[i] == '\'' || str[i] == '"'))
// 		{
// 			lock = str[i];
// 			first = i;
// 		}
// 		else if(lock == str[i])
// 		{
// 			last = i;
// 			if(c < last && c > first)
// 				break;
// 			lock = 0;
// 		}
// 		i++;
// 	}
// 	if(lock == '\"' || h == 'h')
// 		return 1;
// 	else if(lock == '\'')
// 		return -1;
// 	else
// 		return 0;
// }

int len_get_expand_value(char *str)
{
	int i = 0;

	while(str[i] && (ft_isalpha(str[i]) || ft_isnum(str[i]) || str[i] == '_'))
		i++;
	return i;
}
//thydat 256 (fiha mochkil)
char *get_expand_value(char *str)
{
    int j;
		
	if (str[0] == '?')
		return (ft_strdup("?"));
    char *val = malloc(sizeof(char ) * 256);
    j = 0;
    while(*str && (ft_isalpha(*str) || ft_isnum(*str) || *str =='_'))
    {     
        val[j++] = *str;
        str++;
    }
    val[j] = '\0';
    return(val);
}

int	check_equal(char *str, int j)
{
	int i = 0;

	if(str[0] == '=')
		return 0;
	while(str[i] && i < j)
	{
		if(str[i] == '=')
			return 1;
		i++;
	}
	return 0;
}

void	copy(char *dst, const char *src)
{
	size_t	i;
	size_t	j;

	if (!src)
		return ;
	i = 0;
	j = ft_strlen(dst);
	while (src[i] != '\0')
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
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
				copy(tmp, val);
				k += ft_strlen(val);
				i += ft_strlen(key);
            }
            else
                tmp[k++] = str[i++];
        }
    	return(tmp);
    }
    else
       return(str);
}

char *add_quotes_dollar(char *str)
{
	int i;
	int j;
	char *with_quotes;

	if (!str || !str[0])
		return str;
	j = 0;
	i = 0;
	with_quotes = ft_malloc(sizeof(char) * (ft_strlen(str) + 4), 'a');
	if(!with_quotes)
		return 	NULL;
	with_quotes[0] = '"';
	with_quotes[1] = '$';
	i += 2;
	while(str[j])
	{
		with_quotes[i] = str[j];
		i++;
		j++;
	}
	with_quotes[i] = '"';
	with_quotes[i + 1] = '\0';
	return(with_quotes);
}

char *hmad(char *str)
{
	int i;
	int	k;
	char	*tmp = ft_malloc(sizeof(char) * 256, 'a');
	char	*key;
	
	i = 0;
	k = 0;
	if(ft_strchr(str, '$'))
    {  
        while(str[i])
        {
            if(str[i] == '$' && !check_quotes(str, i, 0) && check_equal(str, i))
            {
				i++;
                key = get_expand_value(str + i);
				// if(val == NULL && ft_isnum(key[0]))
				// 	val = key + 1;
				copy(tmp, add_quotes_dollar(key));
				k += ft_strlen(key) + 2;
				i += ft_strlen(key);
            }
            else
                tmp[k++] = str[i++];
        }
    	return(tmp);
    }
	return str;
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
		arg->str = hmad(arg->str);
		tmp = ft_split(expand(arg->str, env, 'a'), "\t\n ");
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