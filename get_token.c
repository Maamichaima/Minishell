#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>

int	is_whitespace(char c)
{
	if (c == ' ')
		return (1);
	return (0);
}

int is_symbol(char c)
{
	if(c == '|' || c == '<' || c == '>' || c == '&')
		return (1);
	return (0);
}

char	*get_next_str(char *s, int *i)
{
	char	*token = malloc(256);
	int j;
	char	lock = 0;
	int	a = 0;

	j = 0;
	while(s[*i] && (lock || (!is_symbol(s[*i]) && !is_whitespace(s[*i]))))
	{
		if (!lock && (s[*i] == '\'' || s[*i] == '\"'))
		{
			lock = s[*i];
			a = *i;
		}
		token[j] = s[*i];
		if (lock == s[*i] && a != *i)
			lock = 0;
		(*i)++;
		j++;
	}
	token[j] = '\0';
	return (token);
}

char	*get_next_symbol(char *s, int *i)
{
	char	*token = malloc(3);
	int j;

	j = 0;
	if(s[*i] && is_symbol(s[*i]))
	{
		token[j] = s[*i];
		(*i)++;
		j++;
	}
	if(s[*i] && s[*i] == token[j - 1])
	{
		token[j] = s[*i];
		(*i)++;
		j++;
	}
	token[j] = '\0';
	return (token);
}

char	*get_next_token(char *s)
{
	static int	i;

	while (s[i] && is_whitespace(s[i]))
		i++;
	if (!s[i])
	{
		i = 0;
		return (NULL);
	}
	if (!is_symbol(s[i]))
		return (get_next_str(s, &i));
	else
		return (get_next_symbol(s, &i));
}

void	print_token(char *s)
{
	char	*token;
	while (1)
	{
		token = get_next_token(s);
		if (!token)
			break ;
		puts(token);
	}
}

