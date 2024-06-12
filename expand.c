/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rraida- <rraida-@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 16:49:47 by rraida-           #+#    #+#             */
/*   Updated: 2024/06/12 20:48:18 by rraida-          ###   ########.fr       */
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

char *get_expand_value(char *str)
{
    int j;
    
    char *val = malloc(sizeof(char ) *256);
    j = 0;
    while(*str && (isalpha(*str) || *str =='_'))
    {     
        val[j++] = *str;
        str++;
    }
    val[j] = '\0';
    return(val);
}

char    *expand(char *str, t_env *env)//
{
    int i;
    int k;
    char *key;
    char *val;
    char *tmp = malloc(sizeof(char ) *256);
    
    i = 0;
    k = 0;
    if(ft_strchr(str,'$'))
    {   
        while(str[i])
        {
            if(str[i] == '$')
            {
                i++;
                key = get_expand_value(str + i);        
                val = get_value_(key,env);
                tmp = ft_strjoin(tmp ,val);
                //printf("%s  %s\n",val,key);
                k += strlen(val);
                i += strlen(key);
            }
            else
            {
                tmp[k] = str[i];
                i++;
                k++;
            }
        }
        tmp[k] = '\0';
        //printf("%s\n",tmp);
    return(tmp);
    }
    else
       return(str);
}

// int main(int ac, char **av, char **env)
// {
    
//     expand("hello$PWD$HOME");
    
// }