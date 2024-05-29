/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maamichaima <maamichaima@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 14:56:59 by cmaami            #+#    #+#             */
/*   Updated: 2024/05/28 21:27:08 by maamichaima      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int	open_here_doc(char *del)
{
	char	*tmp;
	int		pipe_fd[2];

	pipe(pipe_fd);
	while (1)
	{
		write(1, ">", 1);
		tmp = readline("");
		if (!tmp || ft_strcmp(tmp, del) == 0)
		{
			free(tmp);
			break ;
		}
		write(pipe_fd[1], tmp, ft_strlen(tmp));
	}
	close(pipe_fd[1]);
	return (pipe_fd[0]);
}

int	outfile(t_str *red)
{
	int	fd;

	while (red)
	{
		if (red->type == token_apend)
		{
			fd = open(red->str, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (fd == -1)
			{
				perror(red->str);
				exit(1);
			}
		}
		else if (red->type == token_red_output)
		{
			fd = open(red->str, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (fd == -1)
			{
				perror(red->str);
				exit(1);
			}
		}
		red = red->next;
	}
	return (fd);
}

int	infile(t_str *red)
{
	int	fd;

	while (red)
	{
		if (red->type == token_red_input)
		{
			fd = open(red->str, O_WRONLY, 0644);
			if (fd == -1)
			{
				perror(red->str);
				exit(1);
			}
		}
		else if (red->type == token_herd)
			fd = open_here_doc(red->str);
		red = red->next;
	}
	return (fd);
}
